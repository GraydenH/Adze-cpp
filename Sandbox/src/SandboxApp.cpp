#include <Adze.h>

class ExampleLayer : public adze::Layer
{
public:
	ExampleLayer(): Layer("Example")
	{
	}

	void update() override
	{
		ADZE_INFO("ExampleLayer::Update");
	}

	void onEvent(adze::Event& event) override
	{
		//ADZE_TRACE("{0}", event);
	}

};

class SandBox : public adze::Application {
public:
	SandBox() {
		pushLayer(new ExampleLayer());
		pushOverlay(new adze::ImguiLayer());
	}
	~SandBox() {}
};

adze::Application* adze::createApplication() {
	return new SandBox();
}