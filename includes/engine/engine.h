#include "renderer.h"
#include "runtime.h"

#ifndef PROGRAM_ENGINE
#define PROGRAM_ENGINE

namespace engine
{

class Engine
{
    static void parseDebug();

  public:
    static bool IsDebug;

    static Runtime *ProgramRuntime;
    static Renderer *ProgramRenderer;

    static void Run(const char *program_name, size_t max_fps);
};

} // namespace engine

#endif
