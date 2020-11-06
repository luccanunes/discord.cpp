#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "Guild.hpp"
#include "Embed.hpp"
#include "Api.hpp"

namespace dpp {
	class Channel {
	public:
		inline Channel(nlohmann::json& props) {
			id = props["id"];
			type = props["type"];
			if (!props["name"].is_null())
				name = props["name"];
			if (!props["icon"].is_null())
				icon = props["icon"];
			if (!props["topic"].is_null())
				topic = props["topic"];
			if (!props["guild_id"].is_null())
				guild_id = props["guild_id"];
			if (!props["last_message_id"].is_null())
				last_message_id = props["last_message_id"];
		}
		inline Guild guild() {
			nlohmann::json res = Api::get("/guilds/" + guild_id + "?with_counts=true");
			Guild g(res);
			return g;
		}

		int type;
		int position;
		std::string id;
		std::string name;
		std::string icon;
		std::string topic;
		std::string last_message_id;

		inline std::string send(const Embed& embed) const {
			nlohmann::json body = { {"embed", embed.json()} };
			return Api::post("/channels/" + id + "/messages", cpr::Body{ body.dump() }).dump();
		}
		inline std::string send(const std::string& message) const {
			nlohmann::json body = { {"content", message} };
			return Api::post("/channels/" + id + "/messages", cpr::Body{ body.dump() }).dump();
		}
		inline std::string send(const std::string& message, const Embed& embed) const {
			nlohmann::json body = { {"content", message}, {"embed", embed.json()} };
			return Api::post("/channels/" + id + "/messages", cpr::Body{ body.dump() }).dump();
		}

		friend class Client;
		friend class Message;
	protected:
		std::string guild_id;
	};
}