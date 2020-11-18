#include <nlohmann/json.hpp>
#include "Api.h"
#include "User.h"

namespace dpp {
	void User::initialize(nlohmann::json& props) {
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
	std::vector<Guild> User::guilds() const {
		std::vector<Guild> guilds;
		nlohmann::json res = Api::get("/users/@me/guilds");
		for (nlohmann::json guild : res) {
			guilds.push_back(Guild(guild));
		}
		return guilds;
	}
}