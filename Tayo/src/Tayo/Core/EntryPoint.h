#pragma once

#ifdef TY_PLATFORM_WINDOWS

extern Tayo::Application* Tayo::CreateApplication();

int main(int argc,char** argv) {
	Tayo::Log::Init();

	TY_PROFILE_BEGIN_SESSION("Startup", "TayoProfile-Startup.json");
	auto app = Tayo::CreateApplication();
	TY_PROFILE_END_SESSION();

	TY_PROFILE_BEGIN_SESSION("Runtime", "TayoProfile-Runtime.json");
	app->Run();
	TY_PROFILE_END_SESSION();

	TY_PROFILE_BEGIN_SESSION("Shutdown", "TayoProfile-Shutdown.json");
	delete app;
	TY_PROFILE_END_SESSION();
}

#endif // TY_PLATFORM_WINDOWS
