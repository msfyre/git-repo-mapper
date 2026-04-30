#include "renderer.h"
#include "runtime.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <chrono>

Renderer::Renderer(Runtime *runtime, const char *window_name, int w, int h, float fps_cap)
{
    DeltaTime = 0;
    frameDelay = 1.0 / fps_cap;

    SDL_Window *window = SDL_CreateWindow(window_name, w, h, 0);
    SDLRenderer = SDL_CreateRenderer(window, nullptr);

    RuntimeEventCallbackFn call_render_lambda = [this](float runtime_dt, SDL_Event sdl_event) {
        this->callRender(runtime_dt);
    };

    runtime->SubscribeFunction(call_render_lambda);
}

void Renderer::callRender(float runtime_dt)
{
    SDL_Delay((frameDelay * 1000) - runtime_dt);

    auto prevtime = std::chrono::high_resolution_clock::now();

    SDL_SetRenderDrawColor(SDLRenderer, 0, 0, 0, 255);
    SDL_RenderClear(SDLRenderer);

    for (RenderEvent event : events)
    {
        event.callback(this->SDLRenderer, runtime_dt, DeltaTime);
    }

    SDL_RenderPresent(SDLRenderer);

    auto currtime = std::chrono::high_resolution_clock::now();

    DeltaTime = std::chrono::duration<float>(currtime - prevtime).count();
}

RenderEvent Renderer::SubscribeFunction(RenderEventCallbackFn callbackfn)
{
    RenderEvent event = {
        .uid = ++nextCallbackUID,
        .callback = callbackfn,
    };

    events.push_back(event);

    return event;
}
