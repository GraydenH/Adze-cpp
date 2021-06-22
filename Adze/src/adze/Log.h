#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace adze {
	class ADZE_API Log {
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
#define ADZE_CORE_ERROR(...) ::adze::Log::getCoreLogger()->error(__VA_ARGS__)
#define ADZE_CORE_TRACE(...) ::adze::Log::getCoreLogger()->trace(__VA_ARGS__)
#define ADZE_CORE_WARN(...) ::adze::Log::getCoreLogger()->warn(__VA_ARGS__)
#define ADZE_CORE_INFO(...) ::adze::Log::getCoreLogger()->info(__VA_ARGS__)
#define ADZE_CORE_FATAL(...) ::adze::Log::getCoreLogger()->fatal(__VA_ARGS__)

// client log macros
#define ADZE_ERROR(...) ::adze::Log::getClientLogger()->error(__VA_ARGS__)
#define ADZE_TRACE(...) ::adze::Log::getClientLogger()->trace(__VA_ARGS__)
#define ADZE_WARN(...) ::adze::Log::getClientLogger()->warn(__VA_ARGS__)
#define ADZE_INFO(...) ::adze::Log::getClientLogger()->info(__VA_ARGS__)
#define ADZE_FATAL(...) ::adze::Log::getClientLogger()->fatal(__VA_ARGS__)