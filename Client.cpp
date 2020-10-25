#pragma comment(lib, "crypt32")
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include "Client.h"
#include "Api.h"

using json = nlohmann::json;

namespace dpp {
	void Client::run(const std::string& TOKEN) {
		token = TOKEN;
		ix::initNetSystem();

		std::string url("wss://gateway.discord.gg/?v=6&encoding=json");
		webSocket.setUrl(url);

		heartbeat_interval = -1;
		connected = false;

		webSocket.setOnMessageCallback([&](const ix::WebSocketMessagePtr& msg)
			{
				if (msg->type == ix::WebSocketMessageType::Message)
				{
					std::cout << "RESPONSE: " << msg->str << "\n\n";
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
							std::cout << "SENDING HEARTBEAT: " << heartbeat_p.dump() << "\n\n";
							webSocket.send(heartbeat_p.dump());
						}
						sendID();
						break;
					case 0:
						std::string t = res["t"];
						if (t == "READY") {
							std::cout << "USER INFO: " << res["d"]["user"] << "\n\n";
							user.setInfo(res["d"]["user"]);
							if (onReady)
								onReady();
						}
						else if (t == "MESSAGE_CREATE") {
							dpp::Message message(res["d"]);
							if (onMessage)
								onMessage(message);
						}
						break;
					}
				}
				else if (msg->type == ix::WebSocketMessageType::Open)
				{
					std::cout << "Connection established" << "\n\n";
				}
			}
		);

		webSocket.start();

		int count = 0;
		while (true)
		{
			count += 200;
			if (connected && heartbeat_interval != -1 && count >= heartbeat_interval) {
				count = 0;
				json payload = {
					{"op", 1},
					{"d", lastS}
				};
				std::cout << "SENDING HEARTBEAT: " << payload.dump() << "\n\n";
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
		std::cout << "SENDING: " << id.dump() << "\n\n";
		webSocket.send(id.dump());
	}
	void Client::send(const std::string message, const std::string channel_id) {
		std::string hookToken;
		std::string hookID;
		bool alreadyExists = false;

		const std::string getURL = "https://discord.com/api/channels/" + channel_id + "/webhooks";

		json hooks = Api::get(getURL, token);

		for (json hook : hooks) {
			if (hook["channel_id"] == channel_id && hook["name"] == "discord cpp") {
				std::cout << "ALREADY EXISTS" << std::endl;
				alreadyExists = true;
				hookToken = hook["token"];
				hookID = hook["id"];
			}
		}
		if (!alreadyExists) {
			std::cout << "doesnt exist :(" << std::endl;
			const std::string postURL = "https://discord.com/api/channels/" + channel_id + "/webhooks";
			json newHook = Api::post(postURL, cpr::Body{ "{\"name\": \"testando 123\"}" }, token);
			hookToken = newHook["token"];
			hookID = newHook["id"];
		}
		const std::string hookURL = "https://discord.com/api/webhooks/" + hookID + "/" + hookToken;
		if (user.avatar == "null") {
			cpr::Post(
				cpr::Url{ hookURL },
				cpr::Payload{
					{"content", message},
					{"username", user.name},
				}
			);
		}
		else {
			cpr::Post(
				cpr::Url{ hookURL },
				cpr::Payload{
					{"content", message},
					{"username", user.name},
					{"avatar_url", user.avatar}
				}
			);
		}
	}
}