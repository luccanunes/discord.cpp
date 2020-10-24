#pragma comment(lib, "crypt32")
#pragma comment(lib, "ws2_32.lib")

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void sendID(ix::WebSocket& webSocket);

int main()
{
	ix::initNetSystem();

	ix::WebSocket webSocket;

	std::string url("wss://gateway.discord.gg/?v=6&encoding=json");
	webSocket.setUrl(url);

	std::cout << "Connecting to " << url << "..." << std::endl;

	int heartbeat_interval = -1;
	bool connected = false;
	int lastS;
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
					sendID(webSocket);
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
	return 0;
}

void sendID(ix::WebSocket& webSocket)
{
	std::string token = "NzY5MjIwMjEyODA4ODc2MDMz.X5L2Jg.To8C4xQog1OeDdeCTdT9b6lW86o";
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