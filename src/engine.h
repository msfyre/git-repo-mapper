#include "core_engine/renderer.h"
#include "core_engine/runtime.h"

#ifndef PROGRAM_ENGINE
#define PROGRAM_ENGINE

class Engine
{
    static void parseDebug();

  public:
    static bool IsDebug;

    static Runtime *ProgramRuntime;
    static Renderer *ProgramRenderer;

    static void Run(const char *program_name, size_t max_fps);
};

#endif
