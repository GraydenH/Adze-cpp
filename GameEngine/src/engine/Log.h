#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace engine {
	class ENGINE_API Log {
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> clientLogger;
		static std::shared_ptr<spdlog::logger> coreLogger;
	};
}

// core log macros
#define ENGINE_CORE_ERROR(...) ::engine::Log::getCoreLogger()->error(__VA_ARGS__)
#define ENGINE_CORE_TRACE(...) ::engine::Log::getCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_CORE_WARN(...) ::engine::Log::getCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_CORE_INFO(...) ::engine::Log::getCoreLogger()->info(__VA_ARGS__)
#define ENGINE_CORE_FATAL(...) ::engine::Log::getCoreLogger()->fatal(__VA_ARGS__)

// client log macros
#define ENGINE_CLIENT_ERROR(...) ::engine::Log::getClientLogger()->error(__VA_ARGS__)
#define ENGINE_CLIENT_TRACE(...) ::engine::Log::getClientLogger()->trace(__VA_ARGS__)
#define ENGINE_CLIENT_WARN(...) ::engine::Log::getClientLogger()->warn(__VA_ARGS__)
#define ENGINE_CLIENT_INFO(...) ::engine::Log::getClientLogger()->info(__VA_ARGS__)
#define ENGINE_CLIENT_FATAL(...) ::engine::Log::getClientLogger()->fatal(__VA_ARGS__)