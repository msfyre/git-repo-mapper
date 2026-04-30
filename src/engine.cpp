#include "engine.h"
#include "core/renderer.cpp"
#include "core/runtime.cpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <cmath>
#include <cstdio>
#include <string>

bool Engine::IsDebug = false;

Runtime *Engine::ProgramRuntime = nullptr;
Renderer *Engine::ProgramRenderer = nullptr;

void Engine::parseDebug()
{
    printf("%b\n", IsDebug);
}

void Engine::Run(const char *program_name)
{
    Engine::ProgramRuntime = new Runtime();
    Engine::ProgramRenderer = new Renderer(Engine::ProgramRuntime, program_name, 640, 480, 60);

    ProgramRuntime->SubscribeFunction([](float runtime_dt, SDL_Event sdl_event) { Engine::parseDebug(); });
    ProgramRuntime->Execute();
}

void render_debug_information(SDL_Renderer *renderer, float runtime_dt, float render_dt)
{
    std::string fps_string = std::to_string(std::floor(1.0 / runtime_dt));
    std::string ups_string = std::to_string(std::floor(1.0 / render_dt));

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderDebugText(renderer, 5, 5, ((std::string) "FPS: " + fps_string).c_str());
    SDL_RenderDebugText(renderer, 5, 15, ((std::string) "UPS: " + ups_string).c_str());
}
