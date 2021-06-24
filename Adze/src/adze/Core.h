#pragma once

#ifdef ADZE_PLATFORM_WINDOWS
	#ifdef ADZE_BUILD_DLL
		#define ADZE_API __declspec(dllexport)
	#else
		#define ADZE_API __declspec(dllimport)
	#endif
#else
	#error ADZE only supports windows
#endif

#ifdef ADZE_ENABLE_ASSERTS
	#define ADZE_ASSERT(x, ...) { if(!(x)) { ADZE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ADZE_CORE_ASSERT(x, ...) { if(!(x)) { ADZE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ADZE_ASSERT(x, ...)
	#define ADZE_CORE_ASSERT(x, ...)
#endif

#define ADZE_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
	
#define BIT(x) (1 << x) 