#include "Guild.h"

using json = nlohmann::json;

namespace dpp {
	Guild::Guild(json& props) {
		id = props["id"];
		name = props["name"];
		if (!props["icon"].is_null())
			icon = props["icon"];
		if (!props["region"].is_null())
			region = props["region"];
		if (!props["emojis"].is_null())
			emojis = props["emojis"];
		if (!props["owner_id"].is_null())
			owner_id = props["owner_id"];
		if (!props["description"].is_null())
			description = props["description"];
		if (!props["afk_timeout"].is_null())
			afk_timeout = props["afk_timeout"];
		if (!props["widget_enabled"].is_null())
			widget_enabled = props["widget_enabled"];
		if (!props["approximate_member_count"].is_null())
			approximate_member_count = props["approximate_member_count"];

		for (json role : props["roles"]) {
			Role r(role);
			roles.push_back(r);
		}
	}
}