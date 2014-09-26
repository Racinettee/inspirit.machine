#include "../IGameScreen.hpp"
#include <memory>
namespace inspirit
    {
class Engine
      {
static void PushScreen(IGameScreen*);
static shared_gamescreen PopScreen();
static IGameScreen const* CurrentScreen();
static IGameScreen* TopScreen();
static double DeltaT();
};
};
void inspirit
    ::Engine
      ::PushScreen(inspirit::IGameScreen*){ }
inspirit::shared_gamescreen inspirit
    ::Engine
      ::PopScreen(){ }
inspirit::IGameScreen const* inspirit
    ::Engine
      ::CurrentScreen(){ }
inspirit::IGameScreen* inspirit
    ::Engine
      ::TopScreen(){ }
double inspirit
    ::Engine
      ::DeltaT(){ }
