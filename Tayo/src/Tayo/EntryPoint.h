#pragma once

#ifdef TY_PLATFORM_WINDOWS

extern Tayo::Application* Tayo::CreateApplication();

using namespace Tayo;
int main(int argc,char** argv) {
	Tayo::Log::Init();
	TY_CORE_WARN("Initialized Log!");
	int a = 5;
	TY_INFO("It's Log! Var={0}",a);
	auto app = Tayo::CreateApplication();
	app->Run();
	delete app;
}

#endif // TY_PLATFORM_WINDOWS
