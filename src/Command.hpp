#pragma once
#include <functional>
#include <vector>
#include <string>
#include "Message.hpp"

namespace dpp {
	class Command {
	public:
		inline Command(const std::string& name, const std::function<void(const Message& message)>& callback) {
			this->name = name;
			this->callback = callback;
		}
		inline void setAliases(const std::vector<std::string>& aliases) {
			this->aliases = aliases;
		}
		friend class Client;
	private:
		std::string name;
		std::function<void(const Message& message)> callback;
		std::vector<std::string> aliases;
	};
}