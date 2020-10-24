#include <iostream>
#include "Message.h"

namespace dpp {
	Message::Message(nlohmann::json props) {
		tts = props["tts"];
		timestamp = props["timestamp"];
		pinned = props["pinned"];
		mentions = props["mentions"];
		mention_roles = props["mention_roles"];
		embeds = props["embeds"];
		attachments = props["attachments"];
		author = props["author"];
		mention_everyone = props["mention_everyone"];
		member = props["member"];
		id = props["id"];
		flags = props["flags"];
		content = props["content"];
		channel_id = props["channel_id"];
		guild_id = props["guild_id"];
	}
}