#include "Assertion.h"

using namespace Gyvr::Core::Debug;

void Gyvr::Core::Debug::Assert(bool p_condition, const std::string& p_message, const char* p_file, int p_line)
{
	#ifdef _DEBUG
	if (!GET_BOOL(ENGINE, "debug"))
		return;

	if (p_condition)
	{
		const std::string file(p_file);
		const std::string line(std::to_string(p_line));
		const std::string finalMessage(p_message + "(File: " + file + " on line " + line + ")");

		Log::Process(finalMessage, Log::LogLevel::LOG_ERROR);

		system("PAUSE");
		std::exit(EXIT_FAILURE);
	}
	#endif
}
