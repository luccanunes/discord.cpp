#pragma once

#include <vector>
#include <string>
#include "Guild.h"

namespace dpp {
	class User {
	public:
		void initialize(nlohmann::json& props);
		bool bot;
		std::string id;
		std::string name;
		std::string email;
		std::string avatar;
		std::string discriminator;
		std::vector<Guild> guilds() const;
		friend class Client;
		friend class Message;
	};
}