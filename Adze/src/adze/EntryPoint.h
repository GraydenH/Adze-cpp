#pragma once

#ifdef ADZE_PLATFORM_WINDOWS

extern adze::Application* adze::createApplication();

void main(int argc, char** argv) {
	adze::Log::init();
	ADZE_CORE_WARN("init log");
	ADZE_CORE_INFO("hello log");

	auto app = adze::createApplication();
	app->run();
	delete app;
}

#endif