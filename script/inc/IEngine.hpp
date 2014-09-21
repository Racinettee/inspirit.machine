#include <memory>
#include "../../IGameScreen.hpp"
namespace inspirit
{
class Engine
{
public:
	static void PushScreen(IGameScreen*);
	static std::shared_ptr<IGameScreen> PopScreen();
   static IGameScreen* TopScreen();
   static IGameScreen const* CurrentScreen();
	static double DeltaT();
};
};
