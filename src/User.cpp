#include <iostream>
#include "User.h"

namespace dpp {
	void User::initialize(nlohmann::json& props) {
		id = props["id"];
		name = props["username"];
		avatar = props["avatar"].dump();
		discriminator = props["discriminator"];
		if (!props["bot"].is_null())
			bot = props["bot"];
		if (!props["email"].is_null())
			email = props["email"];
	}
}