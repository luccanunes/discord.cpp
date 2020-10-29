#pragma once
#include <string>

namespace dpp {
	std::string urlEncode(const std::string& s);
	void hexChar(unsigned char c, unsigned char& hex1, unsigned char& hex2);
}