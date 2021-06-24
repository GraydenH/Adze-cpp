#pragma once

#include "adze/Core.h"

namespace adze {
	class ADZE_API Input {
	public:
		inline static bool isKeyPressed(int keyCode) {
			return instance->isKeyPressedImpl(keyCode);
		}
		
		inline static bool isMouseButtonPressed(int button) {
			return instance->isMouseButtonPressedImpl(button);
		}
		
		inline static int getMouseX() {
			return instance->getMouseXImpl();
		}
		
		inline static int getMouseY() {
			return instance->getMouseYImpl();
		}
	protected:
		virtual bool isKeyPressedImpl(int keyCode) = 0;
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;

	private:
		static Input* instance;
	};
}