#include <GL/glew.h>
#include <stdio.h>
#include "inc/IEngine.hpp"
// --------------------------
using namespace inspirit;
// ----------------------
class StartScreen : public IGameScreen
{
public:
	virtual void Init() override
	{
		glClearColor(1.0f, 0.8f, 0.8f, 1.0f);
	}
	virtual void Render() const { glClear(GL_COLOR_BUFFER_BIT); }
	virtual void Update(double time) const { }
};
extern "C" void Init()
{
	Engine::PushScreen(new StartScreen());
//	Engine::PopScreen();
}
