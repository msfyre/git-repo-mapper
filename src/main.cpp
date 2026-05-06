#include "../includes/engine/engine.h"

using namespace engine;

int main()
{
    Engine::IsDebug = true;
    Engine::Run("Git Mapper", 60);

    return 0;
}
