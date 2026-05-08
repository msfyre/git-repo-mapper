#include <engine/renderer.hpp>
#include <engine/runtime.hpp>

#ifndef PROGRAM_ENGINE
#define PROGRAM_ENGINE

namespace engine {

using namespace engine::runtime;
using namespace engine::renderer;

class Engine {
    static void parseDebug();

  public:
    static bool IsDebug;

    static Runtime *ProgramRuntime;
    static Renderer *ProgramRenderer;

    static void Run(const char *program_name, size_t max_fps);
};

} // namespace engine

#endif
