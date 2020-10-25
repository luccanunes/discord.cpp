#pragma once

#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include "Channel.h"

namespace dpp {
	class Message {
	public:
		Message(nlohmann::json props);
		Channel channel;
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
		nlohmann::json author;
		nlohmann::json member;
		nlohmann::json attachments;
		nlohmann::json mentions;
		nlohmann::json mention_roles;
		nlohmann::json reactions;
	};
}