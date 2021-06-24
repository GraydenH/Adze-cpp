#pragma once

#include "adzepch.h"

#include "adze/Core.h"
#include "adze/events/Event.h"

namespace adze {

	struct WindowProps {
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string& title = "Adze Engine",
			        unsigned int width = 1280,
			        unsigned int height = 720)
			: title(title), width(width), height(height) {}
	};

	// Interface representing a desktop system based Window
	class ADZE_API Window {
	public:
		using EventCallback = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void update() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		// Window attributes
		virtual void setEventCallback(const EventCallback& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		virtual void* getNativeWindow() const = 0;

		static Window* create(const WindowProps& props = WindowProps());
	};

} 