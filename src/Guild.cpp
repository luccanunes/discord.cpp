#include "Guild.h"

using json = nlohmann::json;

namespace dpp {
	void Guild::initialize(json& props) {
		id = props["id"];
		name = props["name"];
		roles = props["roles"];
		region = props["region"];
		emojis = props["emojis"];
		owner_id = props["owner_id"];
		afk_timeout = props["afk_timeout"];
		approximate_member_count = props["approximate_member_count"];
		if (!props["description"].is_null())
			description = props["description"];
		if (!props["icon"].is_null())
			icon = props["icon"];
		if (!props["widget_enabled"].is_null())
			widget_enabled = props["widget_enabled"];
	}
}