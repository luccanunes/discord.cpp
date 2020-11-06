#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <vector>
#include "Role.hpp"

namespace dpp {
	class Guild {
	public:
		inline Guild(nlohmann::json& props) {
			id = props["id"];
			name = props["name"];
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

			for (nlohmann::json role : props["roles"]) {
				Role r(role);
				roles.push_back(r);
			}
		}
		int afk_timeout;
		int approximate_member_count;
		bool widget_enabled;
		std::string id;
		std::string icon;
		std::string name;
		std::string region;
		std::string owner_id;
		std::string description;
		std::vector<Role> roles;
		nlohmann::json emojis;
		friend class Channel;
	};
}