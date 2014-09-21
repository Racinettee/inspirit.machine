// Will declare names that can be mapped to the jit
//#include "inc/IEngine.hpp"
#include <memory>
#include "../IGameScreen.hpp"
#include "inc/IEngine.hpp"
namespace inspirit
{
void Engine::PushScreen(IGameScreen*) { }
// --------------------------------------
std::shared_ptr<IGameScreen> Engine::PopScreen() { }
// -------------------------------------------------
IGameScreen const* Engine::CurrentScreen() { }
// -------------------------------------------
IGameScreen* Engine::TopScreen() { }
// ---------------------------------
double Engine::DeltaT() { }
};
