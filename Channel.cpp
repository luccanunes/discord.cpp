#include "Channel.h"

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
	}
}