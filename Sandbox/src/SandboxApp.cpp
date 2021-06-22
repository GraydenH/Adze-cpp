#include <Adze.h>

class SandBox : public adze::Application {
public:
	SandBox() {}
	~SandBox() {}
};

adze::Application* adze::createApplication() {
	return new SandBox();
}