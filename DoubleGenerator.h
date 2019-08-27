#pragma once

#include <string>

namespace MyLib {
	class DoubleGenerator
	{
	public:
		static void generateToFile(std::string fileName, size_t quantity);
	};
}

