#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "Embed.h"
#include <vector>


namespace dpp {
	class Webhook {
	public:
		Webhook(const std::string url);
		Webhook(const std::string id, const std::string token);

		std::string send(const std::vector<Embed>& embeds) const;
		std::string send(const std::string& message) const;
		std::string send(const std::string& message, const std::vector<Embed>& embeds) const;

		void setName(const std::string& name);
		void setAvatarUrl(const std::string& avatar_url);
		void setTts(const bool& tts);
	private:
		std::string url;
		std::string post(const cpr::Body& body) const;

		std::string name = "";
		std::string avatar_url = "";
		bool tts = false;
	};
}