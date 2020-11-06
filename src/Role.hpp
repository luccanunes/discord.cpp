#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace dpp {
	class Role {
	public:
		inline Role(nlohmann::json& props) {
			color = props["color"];
			position = props["position"];
			hoist = props["hoist"];
			managed = props["managed"];
			mentionable = props["mentionable"];
			id = props["id"];
			name = props["name"];
			permissions = props["permissions_new"];
		}
		int color;
		int position;
		bool hoist;
		bool managed;
		bool mentionable;
		std::string id;
		std::string name;
		std::string permissions;
	};
}