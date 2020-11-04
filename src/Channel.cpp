#include "Channel.h"
#include "Api.h"

using json = nlohmann::json;

namespace dpp {
	Channel::Channel(nlohmann::json& props) {
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
	std::string Channel::send(const Embed& embed) const {
		json body = { {"embed", embed.json()} };
		return Api::post("/channels/" + id + "/messages", cpr::Body{ body.dump() }).dump();
	}
	std::string Channel::send(const std::string& message) const {
		json body = { {"content", message} };
		return Api::post("/channels/" + id + "/messages", cpr::Body{ body.dump() }).dump();
	}
	std::string Channel::send(const std::string& message, const Embed& embed) const {
		json body = { {"content", message}, {"embed", embed.json()} };
		return Api::post("/channels/" + id + "/messages", cpr::Body{ body.dump() }).dump();
	}
	Guild Channel::guild() {
		json res = Api::get("/guilds/" + guild_id + "?with_counts=true");
		Guild g(res);
		return g;
	}
}