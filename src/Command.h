#pragma once
#include <functional>
#include <vector>
#include <string>
#include "Message.h"

namespace dpp {
	class Command {
	public:
		Command(const std::string& name, const std::function<void(const Message& message)>& callback);
		void setAliases(const std::vector<std::string>& aliases);
		friend class Client;
	private:
		std::string name;
		std::function<void(const Message& message)> callback;
		std::vector<std::string> aliases;
	};
}