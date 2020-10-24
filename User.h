#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace dpp {
	class User {
	public:
		bool bot;
		std::string id;
		std::string name;
		std::string avatar;
		std::string discriminator;
		friend class Client;
	protected:
		void setInfo(nlohmann::json props);
	};
}