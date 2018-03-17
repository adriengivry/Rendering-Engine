#pragma once

#include <string>

#include "Log.h"


/*
 * A macro that holds file info such as file and line number
 */
#define __FILE_INFO__ __FILE__, __LINE__


namespace Gyvr
{
	namespace Core
	{
		namespace Debug
		{
			/*
			 * Static function to call an Assert in debug mode (It print error and shutdown the program)
			 */
			extern void Assert(bool p_condition, const std::string& p_message, const char* p_file, int p_line);
		}
	}
}
