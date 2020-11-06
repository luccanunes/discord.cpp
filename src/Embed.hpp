#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include <string>

namespace dpp {
	class Embed {
	public:
		inline Embed() {
			colour = -1;
			url = "";
			title = "";
			timestamp = "";
			description = "";
		}
		inline void setColour(const int& r, const int& g, const int& b) {
			colour = (r * 65536) + (g * 256) + b;
		}
		inline void setColour(std::string hex) {
			if (hex.at(0) == '#')
				hex = hex.substr(1);
			std::cout << hex << std::endl;
			colour = std::stoul(hex, nullptr, 16);
		}
		inline void setUrl(const std::string& url) {
			this->url = url;
		}
		inline void setTitle(const std::string& title) {
			this->title = title;
		}
		inline void setTimestamp(const std::string& timestamp) {
			this->timestamp = timestamp;
		}
		inline void setDescription(const std::string& description) {
			this->description = description;
		}

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
		inline nlohmann::json json() const {
			nlohmann::json j;
			if (colour >= 0)
				j["color"] = colour;
			if (!url.empty())
				j["url"] = url;
			if (!title.empty())
				j["title"] = title;
			if (!timestamp.empty())
				j["timestamp"] = timestamp;
			if (!description.empty())
				j["description"] = description;
			return j;
		}
	};
}