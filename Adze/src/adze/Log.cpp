#include "adzepch.h"

#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace adze {
	std::shared_ptr<spdlog::logger> Log::clientLogger;
	std::shared_ptr<spdlog::logger> Log::coreLogger;

	void Log::init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		coreLogger = spdlog::stdout_color_mt("engine");
		coreLogger->set_level(spdlog::level::trace);
		
		clientLogger = spdlog::stdout_color_mt("app");
		clientLogger->set_level(spdlog::level::trace);
	}
}
