#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <vector>
#include "Role.h"

namespace dpp {
	class Guild {
	public:
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
	protected:
		void initialize(nlohmann::json& props);
	};
}