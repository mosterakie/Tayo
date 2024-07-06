#include "typch.h"
#include "Application.h"

#include "Tayo/Events/ApplilcationEvent.h"
#include "Tayo/Log.h"

namespace Tayo {
	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1920, 1080);
		TY_TRACE(e);
		while (true);
	}
}