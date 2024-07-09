#pragma once

#include "Tayo/Layer.h"

#include "Tayo/Events/ApplicationEvent.h"
#include "Tayo/Events/KeyEvent.h"
#include "Tayo/Events/MouseEvent.h"

namespace Tayo {
	class TAYO_API ImGuiLayer:public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach()override;
		void OnDetach()override;
		void OnUpdate()override;
		void OnEvent(Event& event)override;
	private:
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
	private:
		float m_Time = 0.0f;
	};
}


