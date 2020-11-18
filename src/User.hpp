#pragma once

#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include "Guild.hpp"

namespace dpp {
	class User {
	public:
		inline void initialize(nlohmann::json& props) {
			id = props["id"];
			name = props["username"];
			avatar = props["avatar"].dump();
			discriminator = props["discriminator"];
			if (!props["bot"].is_null())
				bot = props["bot"];
			else
				bot = false;
			if (!props["email"].is_null())
				email = props["email"];
		}
		inline std::vector<Guild> guilds() const {
			std::vector<Guild> guilds;
			nlohmann::json res = Api::get("/users/@me/guilds");
			for (nlohmann::json guild : res) {
				guilds.push_back(Guild(guild));
			}
			return guilds;
		}
		bool bot;
		std::string id;
		std::string name;
		std::string email;
		std::string avatar;
		std::string discriminator;
		friend class Client;
		friend class Message;
	};
}