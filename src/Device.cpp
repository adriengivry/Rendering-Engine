#include "Device.h"

using namespace Gyvr::Core::System::Context;

void GLFWdeleter::operator()(GLFWwindow* ptr) const
{
	glfwDestroyWindow(ptr);
}

void Gyvr::Core::System::Context::ErrorCallback(int, const char* p_err_str)
{
	Debug::Assert(true, "GLFW Error: " + std::string(p_err_str), __FILE_INFO__);
}

void Gyvr::Core::System::Context::KeyCallback(GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
{
	if (p_action == GLFW_PRESS)
		InputManager::occuringKeyEvents[static_cast<InputManager::Key>(p_key)] = InputManager::KeyState::KEY_DOWN;

	if (p_action == GLFW_RELEASE)
		InputManager::occuringKeyEvents[static_cast<InputManager::Key>(p_key)] = InputManager::KeyState::KEY_UP;
}

void Gyvr::Core::System::Context::MouseCallback(GLFWwindow* p_window, int p_mouseButton, int p_action, int p_mods)
{
	if (p_action == GLFW_PRESS)
		InputManager::occuringMouseEvents[static_cast<InputManager::MouseButton>(p_mouseButton)] = InputManager::MouseButtonState::MOUSE_DOWN;

	if (p_action == GLFW_RELEASE)
		InputManager::occuringMouseEvents[static_cast<InputManager::MouseButton>(p_mouseButton)] = InputManager::MouseButtonState::MOUSE_UP;
}

Device::Device()
{
	m_width = 0;
	m_height = 0;
}

void Device::InitContext()
{
	glfwSetErrorCallback(ErrorCallback);

	const int result = glfwInit();

	Debug::Assert(result == GL_FALSE, "GLFW Error!", __FILE_INFO__);

	m_glfwWindow = std::unique_ptr<GLFWwindow, GLFWdeleter>(glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr));
	glfwMakeContextCurrent(m_glfwWindow.get());

	Debug::Assert(!m_glfwWindow.get(), "GLFW can't create window", __FILE_INFO__);

	glfwSetKeyCallback(m_glfwWindow.get(), KeyCallback);
	glfwSetMouseButtonCallback(m_glfwWindow.get(), MouseCallback);
}

void Device::CloseContext()
{
	glfwTerminate();
}

bool Device::IsActive() { return !glfwWindowShouldClose(m_glfwWindow.get()); }

int Device::GetKey(const int p_key) const
{
	return glfwGetKey(m_glfwWindow.get(), p_key);
}

int Device::GetMouseButton(const int p_mouseButton) const
{
	return glfwGetMouseButton(m_glfwWindow.get(), p_mouseButton);
}

std::pair<double, double>& Device::GetCursorPosition()
{
	glfwGetCursorPos(m_glfwWindow.get(), &m_cursorPosition.first, &m_cursorPosition.second);
	return m_cursorPosition;
}

int Device::GetPressState()
{
	return GLFW_PRESS;
}

int Device::GetReleaseState()
{
	return GLFW_RELEASE;
}

void Device::PollEvents()
{
	glfwPollEvents();
}

void Gyvr::Core::System::Context::Device::SwapBuffers()
{
	glfwSwapBuffers(m_glfwWindow.get());
}
