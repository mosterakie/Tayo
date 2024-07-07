#include "typch.h"
#include "Application.h"

#include "Tayo/Events/AppllicationEvent.h"

#include <GLFW/glfw3.h>

namespace Tayo {
	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::Run() {
		while (m_Running)
		{
			glClearColor(0.2, 0.2, 0.5, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}