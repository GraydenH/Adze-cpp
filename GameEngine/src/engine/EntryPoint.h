#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS

extern engine::Application* engine::createApplication();

void main(int argc, char** argv) {
	engine::Log::init();
	ENGINE_CORE_WARN("init log");
	ENGINE_CORE_INFO("hello log");

	auto app = engine::createApplication();
	app->run();
	delete app;
}

#endif