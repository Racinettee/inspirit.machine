#ifndef INSPIRIT_ENGINE_HPP
#define INSPIRIT_ENGINE_HPP
// ------------------------
#include <stack>
#include <memory>
#include "IGameScreen.hpp"
// -----------------------
namespace inspirit
{
  class Engine
  {
  public:
    // Manipulte the current screen.
    static void PushScreen(IGameScreen*);
    static std::shared_ptr<IGameScreen> PopScreen();
    static IGameScreen* TopScreen();
    static IGameScreen const* CurrentScreen();
    // -----------------------------
    // Exit the program
    static void Quit();
    // ------------------------
    static void Startup();
    // -----------------------------------------
    // Implemented in main.cpp, runs the program
    static void MainLoop();
    // ---------------------------------------
    // Delta time: milliseconds between frames
    static double DeltaT();
  private:
    static double delta_time;
    static std::stack<std::shared_ptr<IGameScreen> > screen_stack;
    static IGameScreen* current_screen;
  };
  // ----------------------------------
  // Engine implementation details
  inline void Engine::PushScreen(IGameScreen* n)
  {
    screen_stack.push(std::shared_ptr<IGameScreen>(n));
    current_screen = n;
    if(!current_screen->_is_loaded){
      current_screen->Load();
      current_screen->IGameScreen::Load();
    }
    current_screen->Init();
  }
  inline std::shared_ptr<IGameScreen> Engine::PopScreen()
  {
    std::shared_ptr<IGameScreen> r = screen_stack.top();
    screen_stack.pop();
    current_screen = screen_stack.top().get();
    current_screen->Init();
    return r;
  }
  inline IGameScreen* Engine::TopScreen()
  {
    return screen_stack.top().get();
  }
  inline IGameScreen const* Engine::CurrentScreen()
  {
    return current_screen;
  }
  inline double Engine::DeltaT()
  {
    return delta_time;
  }
}
#endif // INSPIRIT_ENGINE_HPP
