#include "runtime.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <cstddef>
#include <functional>
#include <vector>

#ifndef PROGRAM_RENDER
#define PROGRAM_RENDER

using RenderEventCallbackFn = std::function<void(SDL_Renderer *renderer, float runtime_dt, float render_dt)>;

struct RenderEvent
{
    size_t uid;
    RenderEventCallbackFn callback;
};

class Renderer
{
    std::vector<RenderEvent> events;

    size_t nextCallbackUID;

    bool isDebugMode;

    void callRender(float deltatime);

  public:
    float DeltaTime;
    SDL_Window *SDLWindow;
    SDL_Renderer *SDLRenderer;

    Renderer(Runtime *runtime, const char *window_name, int w, int h);

    RenderEvent SubscribeFunction(RenderEventCallbackFn callbackfn);
    void UnsubscribeEvent(RenderEvent event);
};

#endif
