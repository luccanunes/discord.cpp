#pragma once

#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include "Channel.h"
#include "User.h"

namespace dpp {
	class Message {
	public:
		Message(nlohmann::json& props);
		User author;
		Channel channel;
		int flags;
		bool tts;
		bool pinned;
		bool mention_everyone;
		std::string id;
		std::string content;
		std::string timestamp;
		std::string guild_id;
		nlohmann::json embeds;
		nlohmann::json member;
		nlohmann::json attachments;
		nlohmann::json mentions;
		nlohmann::json mention_roles;
		nlohmann::json reactions;
		std::string reply(const std::string& message);
		std::string add_mention(const std::string& emoji);
	private:
		std::string channel_id;
	};
}