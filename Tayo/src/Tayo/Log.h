#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
namespace Tayo {
	class TAYO_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros

#define TY_CORE_TRACE(...)		::Tayo::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TY_CORE_INFO(...)		::Tayo::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TY_CORE_WARN(...)		::Tayo::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TY_CORE_ERROR(...)		::Tayo::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TY_CORE_FATAL(...)		::Tayo::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros

#define TY_TRACE(...)			::Tayo::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TY_INFO(...)			::Tayo::Log::GetClientLogger()->info(__VA_ARGS__)
#define TY_WARN(...)			::Tayo::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TY_ERROR(...)			::Tayo::Log::GetClientLogger()->error(__VA_ARGS__)
#define TY_FATAL(...)			::Tayo::Log::GetClientLogger()->fatal(__VA_ARGS__)

