#include <engine/engine.hpp>

using namespace engine;

int main() {
    Engine::IsDebug = true;
    Engine::Run("Git Mapper", 60);

    return 0;
}
