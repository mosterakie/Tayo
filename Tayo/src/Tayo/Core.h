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

#ifdef TY_ENABLE_ASSERTS
	#define TY_ASSERT(x, ...) { if(!(x)) { TY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define TY_CORE_ASSERT(x, ...) { if(!(x)) { TY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define TY_ASSERT(x, ...)
	#define TY_CORE_ASSERT(x, ...)
#endif