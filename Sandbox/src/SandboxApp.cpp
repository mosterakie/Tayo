#include <Tayo.h>

class ExampleLayer : public Tayo::Layer
{
public:
	ExampleLayer()
		:Layer("Example layer")
	{}

	void OnUpdate() override
	{
		TY_INFO("ExampleLayer::Update");
	}

	void OnEvent(Tayo::Event& event) override
	{
		TY_TRACE("{0}", event);
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