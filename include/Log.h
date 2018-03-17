#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "ConfigLoader.h"
#include "Date.h"

namespace Gyvr
{
	namespace Core
	{
		namespace Debug
		{
			/*
			 * Static class to display error messages on the console or a file
			 */
			class Log
			{
			public:
				enum class LogLevel
				{
					LOG_INFO,
					LOG_WARNING,
					LOG_ERROR
				};

				enum class LogMode
				{
					DEFAULT,
					LOG_TO_CONSOLE,
					LOG_TO_FILE,
					LOG_TO_ALL
				};

				static const std::string INFO_HEADER;
				static const std::string WARNING_HEADER;
				static const std::string ERROR_HEADER;
				static const std::string COMPILE_DATE;

				static void Process(const std::string& p_message, LogLevel p_logLevel, LogMode p_logMode = LogMode::DEFAULT);

			private:
				static void PrintToConsole(const std::string& p_message, LogLevel p_logLevel);
				static void PrintToFile(const std::string& p_message, LogLevel p_logLevel);

				static std::string GetLogHeader(LogLevel p_logLevel);
			};
		}
	}
}