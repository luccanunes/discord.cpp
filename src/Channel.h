#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "Guild.h"
#include "Embed.h"

namespace dpp {
	class Channel {
	public:
		Channel(nlohmann::json& props);
		Guild guild();
		int type;
		int position;
		std::string id;
		std::string name;
		std::string icon;
		std::string topic;
		std::string last_message_id;
		std::string send(const Embed& embed) const;
		std::string send(const std::string& message) const;
		std::string send(const std::string& message, const Embed& embed) const;
		friend class Client;
		friend class Message;
	protected:
		std::string guild_id;
	};
}