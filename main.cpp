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
// -------------------------
#include <tinyxml2.h>
// ---------------------------------------
#include <boost/filesystem/operations.hpp>
// ----------------------------------------
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
// ----------------------------------------------
#include <string>
#include <fstream>
// -----------------
using namespace llvm;
// ------------------
Module* InitCPP;
ExecutionEngine* Jit;
SMDiagnostic error;
//LLVMContext context;
// ----------------
string error_str;
// ----------------
// Loadbitcode stuff
// -----------------
Module* LoadBitcodeModule(const char* source_name, const std::string& = "");
void ExposeInternals();
//void BindSymbols(Module* m);
void Engine::Startup()
{
  initGLandWindow();
  // LLVM Intialize Native Target
  // Sets up the ability to jit on 'this' machine
  InitializeNativeTarget();
  // ----------------------
  LLVMContext& context = getGlobalContext();
  // ---------------------------------------------------
  // Maybe initialize a pango font and cairo or someting
  // ----------------------------
  // Check for the startup script
  using namespace boost;
  string fname = "script/Init.cpp";
  if(filesystem::exists(fname.c_str()))
  {
    InitCPP = LoadBitcodeModule(fname.c_str());
    // ---------------------------------
    // ---------------------
    EngineBuilder builder(InitCPP);
    builder.setErrorStr(&error_str);
    Jit = builder.create();
    // --------------------
    ExposeInternals();
    // ----------------------
    // -------------------------
    Function* init_function = InitCPP->getFunction("Init");
    void* ptrInit = Jit->getPointerToFunction(init_function);
    // Call the function from the jit module
    ((void(*)())(intptr_t)ptrInit)();
  }
  else
  {
    // Show a message that script/Init.cpp doesn't exist
    puts((fname + " does not exist").c_str());
  }
}
Module* LoadBitcodeModule(const char* source_name, const std::string& extra)
{
  LLVMContext& context = getGlobalContext();
  using namespace boost;
  if(!filesystem::exists(source_name))
    return nullptr;
  string errors, bitcodename = source_name;
  bitcodename = bitcodename.substr(0, bitcodename.find_last_of("."))+".bc";
  string command = "clang++ -std=c++11 -c ";
  command += source_name;
  command += extra+ " -emit-llvm -o "+bitcodename;//script/Init.bc";
  if(!filesystem::exists(bitcodename.c_str()))//"script/Init.bc"))
    ::system(command.c_str());
  std::time_t tsource = filesystem::last_write_time(source_name);
  std::time_t tbcode = filesystem::last_write_time(bitcodename.c_str());
  // -----------------------
  if(tsource > tbcode)
    ::system(command.c_str());
  OwningPtr<MemoryBuffer> mb;
  FILE* fp = fopen(bitcodename.c_str(), "rb");
  MemoryBuffer::getOpenFile(fileno(fp), bitcodename.c_str(), mb, -1);
  Module* m = ParseBitcodeFile(mb.get(), context, &errors);
  fclose(fp);
  puts(errors.c_str());
  return m;
}
// ---------------------------------------------
void ParseDream(tinyxml2::XMLNode* root, ostream& output, vector<string> names, vector<pair<string,string> >& methods);
void WriteDream(ostream& output, vector<pair<string,string> >& methods);
// ----------------------------------------
#include <dlfcn.h>
// ---------------------
void ExposeInternals()
{
  using namespace boost;
  // Ensure that internals.xml exists
  if(!filesystem::exists("script/Internals.xml"))
    throw re("script/Internals.xml not found");
  // Ensure that internals.ll exists, if not we have to create
  // it by generating the classes and functions from the xml.
  // afterwards we have to strip the names in the file
  // we will then have names to pull with dlsym
  if(!filesystem::exists("script/Internals.ll"))
  {
    string fname = "script/Internals.cpp";
    // Generate it from Internals.cpp, which if not found then we have to quit
    if(!filesystem::exists(fname.c_str()))
    {
      ofstream output(fname.c_str());
      tinyxml2::XMLDocument doc;
      doc.LoadFile("script/Internals.xml");
      tinyxml2::XMLNode* node = doc.FirstChildElement();
      // name tree to keep track of which location we are at
      vector<string> names;
      vector<pair<string,string> > methods;
      // we have to generate it from the xml
      ParseDream(node, output, names, methods);
      WriteDream(output,methods);
    }
    // -----------------------------------------------
    ::system("clang++ --std=c++11 -S -c ./script/Internals.cpp");
    ::system("./script/irstrip ./script/Internals.ll -overwrite");
  }
  // Test to see if the c++ module is newer than the ir
  std::time_t tsource = filesystem::last_write_time("script/Internals.cpp");
  std::time_t tbcode = filesystem::last_write_time("script/Internals.ll");
  // ----------------------------------
  if(tsource > tbcode)
  {
    ::system("clang++ --std=c++11 -S -c ./script/Internals.cpp");
    ::system("./script/irstrip ./script/Internals.ll -overwrite");
  }
  // -------------------------------
  // We should now be able to open Internals.ll and get each symbol line by line
  // ---------------------------------------------------------------------------
  ifstream input("script/Internals.ll");
  void* handle = dlopen(NULL, RTLD_LOCAL | RTLD_LAZY);
  LLVMContext& context = getGlobalContext();
  // -----------------------------
  cerr << "Binding internals loop... " << endl;
  while(!input.eof())
  {
    string name;
    input >> name; //getline(input, name);
    cerr << name << endl;
    //string name;
    //input >> name;
    // -------------
    // we have the mangled name, now we use dlsym to get it
    // ----------------------------------------------------
    // fnct = this program
    // --------------------
    void* fptr = dlsym(handle, name.c_str());
    cerr << fptr << endl;
    cerr << dlerror()<< endl;

    Function* push_fnc = InitCPP->getFunction(name);
    Jit->addGlobalMapping(push_fnc, fptr);
  }
  // ------------
  cerr << "done" << endl;
}
void Engine::PushScreen(IGameScreen* n)
{
  screen_stack.push(std::shared_ptr<IGameScreen>(n));
  current_screen = n;
  if(!current_screen->_is_loaded){
    current_screen->Load();
    current_screen->IGameScreen::Load();
  }
  current_screen->Init();
}
std::shared_ptr<IGameScreen> Engine::PopScreen()
{
  std::shared_ptr<IGameScreen> r = screen_stack.top();
  screen_stack.pop();
  current_screen = screen_stack.top().get();
  current_screen->Init();
  return r;
}
IGameScreen* Engine::TopScreen()
{
  return screen_stack.top().get();
}
IGameScreen const* Engine::CurrentScreen()
{
  return current_screen;
}
double Engine::DeltaT()
{
  return delta_time;
}
