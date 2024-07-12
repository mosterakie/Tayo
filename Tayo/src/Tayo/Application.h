#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"

#include "Tayo/ImGui/ImGuiLayer.h"

#include "Tayo/Renderer/Shader.h"
#include "Tayo/Renderer/Buffer.h"
#include "Tayo/Renderer/VertexArray.h"

namespace Tayo {

	class TAYO_API Application
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
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
	private:
		static Application* s_Instance;
	};

	//Defined in CLIENT
	Application* CreateApplication();

}