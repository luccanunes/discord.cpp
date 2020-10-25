#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace dpp {
	class Channel {
	public:
		int type;
		int position;
		std::string id;
		std::string name;
		std::string icon;
		std::string topic;
		std::string guild_id;
		std::string last_message_id;
		friend class Client;
		friend class Message;
	protected:
		void initialize(nlohmann::json props);
	};
}