#pragma once

#include <string>
#include <ctime>

namespace Gyvr
{
	namespace Util
	{
		/*
		 * Static function used to get the current date as a string (Can be used as a filename, no unsupported chars)
		 */
		extern std::string GetDate();
	}
}