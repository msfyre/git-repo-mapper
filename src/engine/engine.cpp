#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>

#include <engine/engine.hpp>
#include <engine/renderer.hpp>
#include <engine/runtime.hpp>

using namespace engine;

bool Engine::IsDebug = false;

Runtime *Engine::ProgramRuntime = nullptr;
Renderer *Engine::ProgramRenderer = nullptr;

void Engine::Run(const char *program_name, size_t max_fps) {
    Engine::ProgramRuntime = new Runtime(max_fps);
    Engine::ProgramRenderer =
        new Renderer(Engine::ProgramRuntime, program_name, 640, 480);

    ProgramRuntime->Execute();
}
