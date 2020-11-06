#pragma once

#include <nlohmann/json.hpp>
#include <string>

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
		friend class Client;
		friend class Message;
	};
}