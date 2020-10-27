#include <iostream>
#include "Channel.h"
#include "Api.h"

using json = nlohmann::json;

namespace dpp {
	void Channel::initialize(nlohmann::json props) {
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

		const std::string path = "/guilds/" + guild_id + "?with_counts=true";
		json res = Api::get(path);
		guild.initialize(res);
	}
	void Channel::send(std::string message) {
		const std::string path = "/channels/" + id + "/messages";
		json body = { {"content", message} };
		json res = Api::post(path, cpr::Body{ body.dump() });
		std::cout << res << std::endl;
	}
}