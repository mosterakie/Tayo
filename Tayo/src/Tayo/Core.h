#pragma once

#ifdef TY_PLATFORM_WINDOWS
	#ifdef TY_BUILD_DLL
		#define TAYO_API __declspec(dllexport)
	#else
		#define TAYO_API __declspec(dllimport)
	#endif // !TY_BUILD_DLL
#else
	#error Tayo only supportWindow!
#endif // TY_PLATFORM_WINDOW

#define BIT(x) (1<<x)
