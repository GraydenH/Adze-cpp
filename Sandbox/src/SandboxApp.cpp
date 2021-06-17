#include <Engine.h>

class SandBox : public engine::Application {
public:
	SandBox() {}
	~SandBox() {}
};

engine::Application* engine::createApplication() {
	return new SandBox();
}