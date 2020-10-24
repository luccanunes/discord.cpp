#include "Api.h"

using json = nlohmann::json;

namespace Api {
	json get(const std::string URL, const std::string token) {
		const std::string authHeader = "Bot " + token;
		cpr::Response res = cpr::Get(cpr::Url{ URL }, cpr::Header{ {"authorization", authHeader} });
		return json::parse(res.text);
	}
	json post(const std::string URL, cpr::Body body, const std::string token) {
		const std::string authHeader = "Bot " + token;
		cpr::Response res = cpr::Post(
			cpr::Url{ URL },
			body,
			cpr::Header{ {"authorization", authHeader}, {"Content-Type", "application/json"} }
		);
		return json::parse(res.text);
	}
}