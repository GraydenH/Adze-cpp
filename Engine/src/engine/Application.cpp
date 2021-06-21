#include "enginepch.h"

#include "Application.h"
#include "engine/events/ApplicationEvent.h"
#include "engine/Log.h"

engine::Application::Application() {
}

engine::Application::~Application() {
}

void engine::Application::run() {
	WindowResizeEvent e(1280, 720);
	if (e.isInCategory(EventCategoryApplication)) {
		ENGINE_TRACE(e);
	}
	if (e.isInCategory(EventCategoryInput)) {
		ENGINE_TRACE(e);
	}
	while (true);
}
