#pragma once

#include "Core.h"
#include "Window.h"

#include "Events/AppllicationEvent.h"

namespace Tayo {

	class TAYO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//Defined in CLIENT
	Application* CreateApplication();

}