#include "Window.h"

using namespace Gyvr::Core::System;

Window::Window(Gyvr::Util::SharedContext& p_sharedContext) : m_sharedContext(p_sharedContext)
{
	m_device = std::make_unique<Context::Device>();
	m_driver = std::make_unique<Context::Driver>();

	Window::Setup();
}

Window::~Window()
{
	Window::Close();
}

void Window::Update() {}
void Window::Close() {}

void Window::Setup()
{
	m_width =	GET_INT(WINDOW, "width");
	m_height =	GET_INT(WINDOW, "height");
	m_title =	GET_STRING(WINDOW, "title");

	SendDataToDevice();

	m_device->InitContext();
	m_driver->InitContext();
}

void Window::SendDataToDevice() const
{
	m_device->SetWidth(m_width);
	m_device->SetHeight(m_height);
	m_device->SetTitle(m_title);
}

Context::Device* Window::GetDevice() const { return m_device.get();  }
Context::Driver* Window::GetDriver() const { return m_driver.get(); }
bool Window::IsOpen() const { return m_device->IsActive(); }
