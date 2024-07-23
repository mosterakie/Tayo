#pragma once

#include "Core.h"
#include "Tayo/Events/Event.h"
#include "Tayo/Core/Timestep.h"

namespace Tayo {
	class TAYO_API Layer 
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}			
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const;
	protected:
		std::string m_DebugName;
	};
}