#include "Adze.h"

class ExampleLayer : public adze::Layer
{
public:
	ExampleLayer(): Layer("Example") {}

	void update() override {
		if (adze::Input::isKeyPressed(ADZE_KEY_TAB)) {
			ADZE_TRACE("Tab key is pressed (poll)!");
		}
	}

	void onEvent(adze::Event& event) override {
		if (event.getEventType() == adze::EventType::KeyPressed) {
			adze::KeyPressedEvent& e = (adze::KeyPressedEvent&)event;
			if (e.GetKeyCode() == ADZE_KEY_TAB) {
				ADZE_TRACE("Tab key is pressed (event)!");
			}
			ADZE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public adze::Application {
public:
	Sandbox() {
		pushLayer(new ExampleLayer());
		pushOverlay(new adze::ImguiLayer());
	}

	~Sandbox() {

	}

};

adze::Application* adze::createApplication() {
	return new Sandbox();
}