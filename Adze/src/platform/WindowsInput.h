#pragma once

#include "adze/Input.h"

namespace adze {
	class WindowsInput : public Input {
	protected:
		virtual bool isKeyPressedImpl(int keyCode) override;
		virtual bool isMouseButtonPressedImpl(int button) override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;
	};
}