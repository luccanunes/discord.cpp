#pragma once

#include <functional>
#include "Message.h"

namespace dpp {
	class Command {
	public:
		void setCallback(std::function<void(const Message& message)>& callback);
	private:
		std::function<void(const Message& ctx)> callback;
	};
}