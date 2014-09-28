/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cpp
 * Copyright (C) 2014 Steve Phillips <StevePhillipsCa@gmail.com>
 *
 * Thing is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Thing is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.";
 */
#include <stack>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Engine.hpp"
#include "IGameScreen.hpp"
// -------------------
using namespace std;
using namespace inspirit;
// --------------------
using re = runtime_error;
// -------------------------
GLFWwindow* window = nullptr;
// ---------------------------
// ---------------------
int main() try
{
	Engine::Startup();

	Engine::MainLoop();

	glfwTerminate();
	return EXIT_SUCCESS;
}
catch(exception& e)
{
	puts(e.what());
	return EXIT_FAILURE;
}
// ------------------------------
// -----------------------
static void error_callback(int error, const char* desc);
static void key_callback(GLFWwindow*, int key, int scancode, int action, int mods);
static void mouse_button_callback(GLFWwindow *, int btn, int actn, int mod);
// -----------------------
void initGLandWindow()
{
	// --------------------------
	if(!glfwInit())
	{
		glfwTerminate();
		throw re("GLFW init failed");
	}
	glfwSetErrorCallback(error_callback);
	// create a windowed mode window and the context
	window = glfwCreateWindow(
	   640, 480, "A thing", nullptr, nullptr);
	// ---------------------------------------
	if(!window)
	{
		glfwTerminate();
		throw re("Window not created");
	}
	glfwMakeContextCurrent(window);
	// ---------------------------
	glewInit();
	// ---------------------------
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
}
static void error_callback(int error, const char* desc)
{
  printf("GLFW Error Code: %i, %s", error, desc);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  Engine::CurrentScreen()->OnKeyPress(key, action);
}
static void mouse_button_callback(GLFWwindow *, int btn, int actn, int mod)
{
  Engine::CurrentScreen()->OnMouseClick(btn, actn);
}
// ----------------------------------------
stack<shared_ptr<IGameScreen> > inspirit::Engine::screen_stack;
double inspirit::Engine::delta_time = 0.0;
IGameScreen* inspirit::Engine::current_screen = nullptr;
// -----------------------------------------------------
void Engine::MainLoop()
{
  // ----------------------------
  /* Loop until the main window is closed */
  while(!glfwWindowShouldClose(window))
  {
    double t1 = glfwGetTime();
    // Update here
    CurrentScreen()->Update(DeltaT());//current_screen->Update();
    // Render here
    CurrentScreen()->Render();//current_screen->Render();
    // Swap buffers
    glfwSwapBuffers(window);
    // ---------------------
    // Poll for events
    glfwPollEvents();
    delta_time = glfwGetTime() - t1;
  }
}
