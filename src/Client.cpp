#pragma comment(lib, "crypt32")
#pragma comment(lib, "ws2_32.lib")

#include <stdexcept>
#include "Client.h"
#include "Api.h"

using json = nlohmann::json;

namespace dpp {
	void Client::run(const std::string& TOKEN) {
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
				json res = json::parse(msg->str);
				if (res["s"].is_number())
					lastS = res["s"];
				int op = std::stoi(res["op"].dump());
				switch (op) {
				case 10:
					heartbeat_interval = std::stoi(res["d"]["heartbeat_interval"].dump());
					if (!connected) {
						connected = true;
						json heartbeat_p = {
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
			if (isTokenInvalid) throw std::invalid_argument("Invalid token: 4004");
			count += 200;
			if (connected && heartbeat_interval != -1 && count >= heartbeat_interval) {
				count = 0;
				json payload = {
					{"op", 1},
					{"d", lastS}
				};
				webSocket.send(payload.dump());
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
	}
	void Client::sendID() {
		json props = { {"$os", "linux"}, {"$browser", "discord_cpp"}, {"$device", "discord_cpp"} };
		json id = {
			{"op", 2},
			{"d", {
				{"token", token}, {"properties", props}, {"intents", 513}
			}}
		};
		webSocket.send(id.dump());
	}
	void Client::send(const std::string& message, const std::string& channel_id) const {
		json body = { {"content", message} };
		json res = Api::post("/channels/" + channel_id + "/messages", cpr::Body{ body.dump() });
	}
	void Client::add_command(const Command& command) {
		commands.push_back(command);
	}
}