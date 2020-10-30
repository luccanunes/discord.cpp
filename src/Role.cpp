#include "Role.h"

using json = nlohmann::json;

namespace dpp {
	Role::Role(json& props) {
		color = props["color"];
		position = props["position"];
		hoist = props["hoist"];
		managed = props["managed"];
		mentionable = props["mentionable"];
		id = props["id"];
		name = props["name"];
		permissions = props["permissions_new"];
	}
}