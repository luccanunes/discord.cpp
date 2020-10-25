#include <iostream>
#include "User.h"

namespace dpp {
	void User::initialize(nlohmann::json props) {
		id = props["id"];
		bot = props["bot"];
		name = props["username"];
		avatar = props["avatar"].dump();
		discriminator = props["discriminator"];
	}
}