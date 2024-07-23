#pragma once

#include "Tayo/Core/Layer.h"

#include "Tayo/Events/ApplicationEvent.h"
#include "Tayo/Events/KeyEvent.h"
#include "Tayo/Events/MouseEvent.h"

namespace Tayo {
	class TAYO_API ImGuiLayer:public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}


