#include "src/engine.cpp"
#include "src/engine.h"

int main()
{
    Engine::IsDebug = true;
    Engine::Run("Git Mapper", 60);

    return 0;
}
