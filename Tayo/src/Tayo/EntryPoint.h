#pragma once

#ifdef TY_PLATFORM_WINDOWS

extern Tayo::Application* Tayo::CreateApplication();

int main(int argc,char** argv) {
	auto app = Tayo::CreateApplication();
	app->Run();
	delete app;
}

#endif // TY_PLATFORM_WINDOWS
