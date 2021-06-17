#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS

extern engine::Application* engine::createApplication();

void main(int argc, char** argv) {
	auto app = engine::createApplication();
	app->run();
	delete app;
}

#endif