#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace dpp {
	class Embed {
	public:
		Embed();
		void setColour(const int& r, const int& g, const int& b);
		void setColour(std::string hex);
		void setUrl(const std::string& url);
		void setTitle(const std::string& title);
		void setTimestamp(const std::string& timestamp);
		void setDescription(const std::string& description);
		friend class Client;
		friend class Channel;
		friend class Message;
		friend class Webhook;
	private:
		int colour;
		std::string url;
		std::string title;
		std::string timestamp;
		std::string description;
		nlohmann::json json() const;
	};
}