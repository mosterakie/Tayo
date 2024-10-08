#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Tayo/Events/ApplicationEvent.h"

#include "Tayo/ImGui/ImGuiLayer.h"

#include "Tayo/Core/Timestep.h"

namespace Tayo {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	//Defined in CLIENT
	Application* CreateApplication();

}