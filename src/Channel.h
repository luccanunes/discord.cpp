#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "Guild.h"

namespace dpp {
	class Channel {
	public:
		Guild guild;
		int type;
		int position;
		std::string id;
		std::string name;
		std::string icon;
		std::string topic;
		std::string last_message_id;
		void send(const std::string& message);
		friend class Client;
		friend class Message;
	protected:
		std::string guild_id;
		void initialize(nlohmann::json& props);
	};
}