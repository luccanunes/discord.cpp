#pragma once

#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include "Channel.hpp"
#include "Embed.hpp"
#include "User.hpp"
#include "urlEncode.hpp"

namespace dpp {
	class Message {
	public:
		inline Message(nlohmann::json& props) {
			tts = props["tts"];
			timestamp = props["timestamp"];
			pinned = props["pinned"];
			mention_roles = props["mention_roles"];
			embeds = props["embeds"];
			attachments = props["attachments"];
			mention_everyone = props["mention_everyone"];
			member = props["member"];
			id = props["id"];
			content = props["content"];
			channel_id = props["channel_id"];
			if (!props["flags"].is_null())
				flags = props["flags"];
			if (!props["mentions"].is_null())
				mentions = props["mentions"];
			if (!props["guild_id"].is_null())
				guild_id = props["guild_id"];
			if (!props["reactions"].is_null())
				reactions = props["reactions"];

			author.initialize(props["author"]);
		}
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
		inline Channel channel() const {
			nlohmann::json res = Api::get("/channels/" + channel_id);
			Channel c(res);
			return c;
		}

		inline std::string reply(const Embed& embed) const {
			nlohmann::json body = {
				{"content", "<@" + author.id + "> "},
				{"embed", embed.json()},
				{"allowed_mentions", {
					{"users", {author.id}}
				}}
			};
			return Api::post("/channels/" + channel_id + "/messages", cpr::Body{ body.dump() }).dump();
		}
		inline std::string reply(const std::string& message) const {
			nlohmann::json body = {
				{"content", "<@" + author.id + "> " + message},
				{"allowed_mentions", {
					{"users", {author.id}}
				}}
			};
			return Api::post("/channels/" + channel_id + "/messages", cpr::Body{ body.dump() }).dump();
		}
		inline std::string reply(const std::string& message, const Embed& embed) const {
			nlohmann::json body = {
				{"content", "<@" + author.id + "> " + message},
				{"embed", embed.json()},
				{"allowed_mentions", {
					{"users", {author.id}}
				}}
			};
			return Api::post("/channels/" + channel_id + "/messages", cpr::Body{ body.dump() }).dump();
		}

		inline std::string add_reaction(const std::string& emoji) const {
			return Api::put("/channels/" + channel_id + "/messages/" + id + "/reactions/" + urlEncode(emoji) + "/@me").dump();
		}
		inline std::string remove_my_reaction(const std::string& emoji) const {
			return Api::del("/channels/" + channel_id + "/messages/" + id + "/reactions/" + urlEncode(emoji) + "/@me").dump();
		}
		inline bool startsWith(const std::string& s) const {
			return content.find(s) == 0;
		}
	};
}