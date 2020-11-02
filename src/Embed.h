#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace dpp {
	class Embed {
	public:
		Embed();
		void setColour(const int& colour);
		void setUrl(const std::string& url);
		void setTitle(const std::string& title);
		void setTimestamp(const std::string& timestamp);
		void setDescription(const std::string& description);
		friend class Client;
		friend class Channel;
		friend class Message;
	private:
		int colour;
		std::string url;
		std::string title;
		std::string timestamp;
		std::string description;
		std::string json_str() const;
	};
}