#include <Tayo.h>

class Sandbox : public Tayo::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
	 
};

Tayo::Application* Tayo::CreateApplication() {
	return new Sandbox();
}