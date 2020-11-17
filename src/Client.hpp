#pragma once
#pragma comment(lib, "crypt32")
#pragma comment(lib, "ws2_32.lib")

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <nlohmann/json.hpp>
#include <functional>
#include <stdexcept>
#include <string>
#include "Message.hpp"
#include "User.hpp"
#include "Api.hpp"
#include "Command.hpp"

namespace dpp {
	class Client {
	public:
		dpp::User user;
		inline void run(const std::string& TOKEN) {
			token = TOKEN;
			Api::initialize(TOKEN);
			ix::initNetSystem();

			std::string url("wss://gateway.discord.gg/?v=6&encoding=json");
			webSocket.setUrl(url);

			heartbeat_interval = -1;
			connected = false;

			webSocket.setOnMessageCallback([&](const ix::WebSocketMessagePtr& msg) {
				if (isTokenInvalid) return;
				if (msg->type == ix::WebSocketMessageType::Message) {
					nlohmann::json res = nlohmann::json::parse(msg->str);
					if (res["s"].is_number())
						lastS = res["s"];
					int op = std::stoi(res["op"].dump());
					switch (op) {
					case 10:
						heartbeat_interval = std::stoi(res["d"]["heartbeat_interval"].dump());
						if (!connected) {
							connected = true;
							nlohmann::json heartbeat_p = {
								{"op", 1},
								{"d", nullptr}
							};
							webSocket.send(heartbeat_p.dump());
						}
						sendID();
						break;
					case 0:
						std::string t = res["t"];
						if (t == "READY") {
							user.initialize(res["d"]["user"]);
							if (onReady)
								onReady();
						}
						else if (t == "MESSAGE_CREATE") {
							dpp::Message message(res["d"]);
							if (onMessage)
								onMessage(message);
							for (Command c : commands) {
								if (message.startsWith(c.name)) {
									c.callback(message);
									break;
								}
								for (std::string alias : c.aliases)
									if (message.startsWith(alias)) c.callback(message);
							}
						}
						break;
					}
				}
				else if (msg->type == ix::WebSocketMessageType::Open) {
				}
				else if (msg->type == ix::WebSocketMessageType::Close) {
					switch (msg->closeInfo.code) {
					case 4004:
						isTokenInvalid = true;
						break;
					}
				}
				}
			);

			webSocket.start();

			int count = 0;
			while (true)
			{
				if (isTokenInvalid) throw std::invalid_argument("invalid token");
				count += 200;
				if (connected && heartbeat_interval != -1 && count >= heartbeat_interval) {
					count = 0;
					nlohmann::json payload = {
						{"op", 1},
						{"d", lastS}
					};
					webSocket.send(payload.dump());
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
			}
		}
		inline void send(const std::string message, const std::string channel_id) const {
			nlohmann::json body = { {"content", message} };
			nlohmann::json res = Api::post("/channels/" + channel_id + "/messages", cpr::Body{ body.dump() });
		}

		inline void add_command(const Command& command) {
			commands.push_back(command);
		}

		std::function<void(const Message& message)> onMessage;
		std::function<void()> onReady;
	private:
		ix::WebSocket webSocket;
		int heartbeat_interval;
		int lastS;
		bool connected;
		std::string token;
		bool isTokenInvalid;
		std::vector<Command> commands;

		inline void sendID() {
			nlohmann::json props = { {"$os", "linux"}, {"$browser", "discord_cpp"}, {"$device", "discord_cpp"} };
			nlohmann::json id = {
				{"op", 2},
				{"d", {
					{"token", token}, {"properties", props}, {"intents", 513}
				}}
			};
			webSocket.send(id.dump());
		}
	};
}