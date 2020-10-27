#include "Message.h"
#include "Api.h"
#include <iostream>

using json = nlohmann::json;

namespace dpp {
	Message::Message(json props) {
		tts = props["tts"];
		timestamp = props["timestamp"];
		pinned = props["pinned"];
		mention_roles = props["mention_roles"];
		embeds = props["embeds"];
		attachments = props["attachments"];
		author = props["author"];
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
		const std::string path = "/channels/" + channel_id;
		json res = Api::get(path);
		channel.initialize(res);
	}
}