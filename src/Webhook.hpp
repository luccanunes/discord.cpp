#pragma once

#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <vector>
#include <string>
#include "Embed.hpp"


namespace dpp {
	class Webhook {
	public:
		inline Webhook(const std::string url) {
			this->url = url;
		}
		inline Webhook(const std::string id, const std::string token) {
			this->url = "https://discord.com/api/webhooks/" + id + "/" + token;
		}

		inline std::string send(const std::vector<Embed>& embeds) const {
			std::vector<nlohmann::json> embedArray;
			for (Embed e : embeds)
				embedArray.push_back(e.json());
			nlohmann::json body = { {"embeds", embedArray} };
			if (name.length() != 0) body["username"] = name;
			if (avatar_url.length() != 0) body["avatar_url"] = avatar_url;
			if (tts) body["tts"] = tts;

			return post(cpr::Body{ body.dump() });
		}
		inline std::string send(const std::string& message) const {
			nlohmann::json body = { {"content", message} };
			if (name.length() != 0) body["username"] = name;
			if (avatar_url.length() != 0) body["avatar_url"] = avatar_url;
			if (tts) body["tts"] = tts;

			return post(cpr::Body{ body.dump() });
		}
		inline std::string send(const std::string& message, const std::vector<Embed>& embeds) const {
			std::vector<nlohmann::json> embedArray;
			for (Embed e : embeds)
				embedArray.push_back(e.json());
			nlohmann::json body = { {"content", message}, {"embeds", embedArray} };
			if (name.length() != 0) body["username"] = name;
			if (avatar_url.length() != 0) body["avatar_url"] = avatar_url;
			if (tts) body["tts"] = tts;

			return post(cpr::Body{ body.dump() });
		}

		inline void setName(const std::string& name) {
			this->name = name;
		}
		inline void setAvatarUrl(const std::string& avatar_url) {
			this->avatar_url = avatar_url;
		}
		inline void setTts(const bool& tts) {
			this->tts = tts;
		}
	private:
		std::string url;

		inline std::string post(const cpr::Body& body) const {
			cpr::Response res = cpr::Post(
				cpr::Url{ url },
				body,
				cpr::Header{ {"Content-Type", "application/json"} }
			);
			return res.text;
		}

		std::string name = "";
		std::string avatar_url = "";
		bool tts = false;
	};
}