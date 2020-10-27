#pragma once
#pragma comment(lib, "crypt32")
#pragma comment(lib, "ws2_32.lib")

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <nlohmann/json.hpp>
#include <functional>
#include <string>
#include "Message.h"
#include "User.h"

namespace dpp {
	class Client {
	public:
		dpp::User user;
		void run(const std::string& TOKEN);
		void send(const std::string message, const std::string channel_id);
		//void(*onMessage)(dpp::Message message);
		std::function<void(Message message)> onMessage;
		//void(*onReady)();
		std::function<void()> onReady;
	private:
		ix::WebSocket webSocket;
		int heartbeat_interval;
		int lastS;
		bool connected;
		std::string token;
		void sendID();
	};
}