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
	void Channel::send(const std::string& message) {
		const std::string path = "/channels/" + id + "/messages";
		json body = { {"content", message} };
		json res = Api::post(path, cpr::Body{ body.dump() });
	}
	Guild Channel::guild() {
		json res = Api::get("/guilds/" + guild_id + "?with_counts=true");
		Guild g(res);
		return g;
	}
}