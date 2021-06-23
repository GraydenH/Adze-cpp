#include <Adze.h>

class SandBox : public adze::Application {
public:
	SandBox() {
		//pushLayer(new ExampleLayer());
		pushOverlay(new adze::ImguiLayer());
	}
	~SandBox() {}
};

adze::Application* adze::createApplication() {
	return new SandBox();
}