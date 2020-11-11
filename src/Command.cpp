#include "Command.h"

namespace dpp {
	Command::Command(const std::string& name, const std::function<void(const Message& message)>& callback) {
		this->name = name;
		this->callback = callback;
	}
}