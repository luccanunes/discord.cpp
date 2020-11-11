#pragma once
#include <functional>
#include <string>
#include "Message.h"

namespace dpp {
	class Command {
	public:
		Command(const std::string& name, const std::function<void(const Message& message)>& callback);
		friend class Client;
	private:
		std::string name;
		std::function<void(const Message& message)> callback;
	};
}