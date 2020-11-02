#pragma once

#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include "Channel.h"
#include "User.h"
#include "Embed.h"

namespace dpp {
	class Message {
	public:
		Message(nlohmann::json& props);
		User author;
		int flags;
		bool tts;
		bool pinned;
		bool mention_everyone;
		std::string id;
		std::string content;
		std::string timestamp;
		std::string guild_id;
		std::string channel_id;
		nlohmann::json embeds;
		nlohmann::json member;
		nlohmann::json attachments;
		nlohmann::json mentions;
		nlohmann::json mention_roles;
		nlohmann::json reactions;
		Channel channel();
		std::string reply(const Embed& embed);
		std::string reply(const std::string& message);
		std::string reply(const std::string& message, const Embed& embed);
		std::string add_reaction(const std::string& emoji);
		std::string remove_my_reaction(const std::string& emoji);
		bool startsWith(const std::string& s);
	};
}