#include <iostream>
#include "User.h"

namespace dpp {
	/*User::User(nlohmann::json props) {
		id = props["id"];
		bot = props["bot"];
		name = props["username"];
		avatar = props["avatar"].dump();
		discriminator = props["discriminator"];
	}*/
	void User::setInfo(nlohmann::json props) {
		id = props["id"];
		bot = props["bot"];
		name = props["username"];
		avatar = props["avatar"].dump();
		discriminator = props["discriminator"];
	}
}