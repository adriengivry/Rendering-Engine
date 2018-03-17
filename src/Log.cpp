#include "Log.h"

using namespace Gyvr::Core::Debug;

std::string const Log::INFO_HEADER		= "[INFO] ";
std::string const Log::WARNING_HEADER	= "[WARNING] ";
std::string const Log::ERROR_HEADER		= "[ERROR] ";
std::string const Log::COMPILE_DATE		= Gyvr::Util::GetDate();

void Log::Process(const std::string& p_message, const LogLevel p_logLevel, const LogMode p_logMode)
{
	#ifdef _DEBUG
	if (!GET_BOOL(ENGINE, "debug"))
		return;

	switch (p_logLevel)
	{
	case LogLevel::LOG_INFO:
		if (!GET_BOOL(ENGINE, "log_info"))
			return;
		break;
	case LogLevel::LOG_WARNING:
		if (!GET_BOOL(ENGINE, "log_warning"))
			return;
		break;
	case LogLevel::LOG_ERROR:
		if (!GET_BOOL(ENGINE, "log_error"))
			return;
		break;
	}

	switch (p_logMode)
	{
	case LogMode::DEFAULT:
		if (GET_BOOL(ENGINE, "log_to_console"))
			PrintToConsole(p_message, p_logLevel);

		if (GET_BOOL(ENGINE, "log_to_file"))
			PrintToFile(p_message, p_logLevel);
		break;

	case LogMode::LOG_TO_CONSOLE:
		PrintToConsole(p_message, p_logLevel);
		break;

	case LogMode::LOG_TO_FILE:
		PrintToFile(p_message, p_logLevel);
		break;

	case LogMode::LOG_TO_ALL:
		PrintToConsole(p_message, p_logLevel);
		PrintToFile(p_message, p_logLevel);
		break;
	}
	#endif
}

void Log::PrintToConsole(const std::string& p_message, const LogLevel p_logLevel)
{
	std::ostream& output = p_logLevel == LogLevel::LOG_INFO || p_logLevel == LogLevel::LOG_WARNING ? std::cout : std::cerr;

	output << GetLogHeader(p_logLevel) << p_message << std::endl;
}

void Log::PrintToFile(const std::string& p_message, const LogLevel p_logLevel)
{
	std::ofstream outfile;
	const std::string filename = "../logs/" + COMPILE_DATE + ".txt";
	outfile.open(filename, std::ios_base::app);
	outfile << GetLogHeader(p_logLevel) << p_message << std::endl;
}

std::string Log::GetLogHeader(const LogLevel p_logLevel)
{
	switch (p_logLevel)
	{
	case LogLevel::LOG_INFO:	return INFO_HEADER;
	case LogLevel::LOG_WARNING:	return WARNING_HEADER;
	case LogLevel::LOG_ERROR:	return ERROR_HEADER;
	}

	return "";
}
