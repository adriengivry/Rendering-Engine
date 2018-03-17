#include "Driver.h"

using namespace Gyvr::Core::System::Context;

Driver::Driver()
{
	m_active = false;
}

void Driver::InitContext()
{
	const auto err = glewInit();

	Debug::Assert(err, "GLEW error: " + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))), __FILE_INFO__);

	m_active = true;
}

bool Driver::IsActive() { return m_active; }

void Gyvr::Core::System::Context::Driver::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}