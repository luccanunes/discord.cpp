#pragma once
#include <functional>
#include <string>
#include "Message.hpp"

namespace dpp {
	class Command {
	public:
		inline Command(const std::string& name, const std::function<void(const Message& message)>& callback) {
			this->name = name;
			this->callback = callback;
		}
		friend class Client;
	private:
		std::string name;
		std::function<void(const Message& message)> callback;
	};
}