#include <Tayo.h>

#include "imgui/imgui.h"

class ExampleLayer : public Tayo::Layer
{
public:
	ExampleLayer()
		:Layer("Example layer")
	{}

	void OnUpdate() override
	{
		if (Tayo::Input::IsKeyPressed(TY_KEY_TAB))
			TY_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Text");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Tayo::Event& event) override
	{
		if (event.GetEventType() == Tayo::EventType::KeyPressed)
		{
			Tayo::KeyPressedEvent& e = (Tayo::KeyPressedEvent&)event;
			if (e.GetKeyCode() == TY_KEY_TAB)
				TY_TRACE("Tab key is pressed (event)!");
			TY_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Tayo::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
	 
};

Tayo::Application* Tayo::CreateApplication() {
	return new Sandbox();
}