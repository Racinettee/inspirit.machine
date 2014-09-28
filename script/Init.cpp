#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "../Engine.hpp"
// --------------------------
using namespace inspirit;
// ----------------------
class SecondScreen: public IGameScreen
{
	virtual void Init() override
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}
	virtual void Render() const { glClear(GL_COLOR_BUFFER_BIT); }
	virtual void Update(double time) const { }
	virtual void OnKeyPress(int key, int action) const override
	{
		if(action == GLFW_PRESS)
			Engine::PopScreen();
	}
};
class StartScreen : public IGameScreen
{
public:
	virtual void Init() override
	{
		glClearColor(0.0f, 0.8f, 0.8f, 1.0f);
	}
	virtual void Render() const { glClear(GL_COLOR_BUFFER_BIT); }
	virtual void Update(double time) const { }
	virtual void OnKeyPress(int key, int action) const override
	{
		if(action == GLFW_PRESS)
			Engine::PushScreen(new SecondScreen());
	}
};
extern "C" void Init()
{
	Engine::PushScreen(new StartScreen());
}
