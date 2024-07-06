#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Tayo {

	class TAYO_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	//Defined in CLIENT
	Application* CreateApplication();
}