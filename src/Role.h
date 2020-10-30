#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace dpp {
	class Role {
	public:
		Role(nlohmann::json& props);
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