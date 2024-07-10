#include "typch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Input.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)

namespace Tayo {
	Application* Application::s_Instance = nullptr;

	Application::Application() 
	{
		TY_CORE_ASSERT(!s_Instance,"Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallbcak(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application() {

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto iter = m_LayerStack.end(); iter != m_LayerStack.begin();)
		{
			(*--iter)->OnEvent(e);
			if (e.Handled)
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverLay(overlay);
		overlay->OnAttach();
	}

	void Application::Run() {
		while (m_Running)
		{
			glClearColor(0.2, 0.2, 0.5, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)				
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}
}