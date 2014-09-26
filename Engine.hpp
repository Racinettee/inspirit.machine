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
}
#endif // INSPIRIT_ENGINE_HPP
