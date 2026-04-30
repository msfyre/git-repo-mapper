#include "runtime.h"
#include <SDL3/SDL_events.h>
#include <chrono>
#include <cstdio>

Runtime::Runtime()
{
    DeltaTime = 0;
    isRunning = false;
    nextCallbackFnUID = 0;
}

void Runtime::Execute()
{
    auto prevtime = std::chrono::high_resolution_clock::now();

    isRunning = true;

    while (isRunning)
    {
        SDL_Event sdl_event;

        while (SDL_PollEvent(&sdl_event))
        {
            if (sdl_event.type == SDL_EVENT_QUIT)
            {
                isRunning = false;
            }
        }

        for (RuntimeEvent event : events)
        {
            event.callback(DeltaTime, sdl_event);
        }

        auto currtime = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float> delayduration = currtime - prevtime;

        DeltaTime = delayduration.count();

        prevtime = currtime;
    }

    std::printf("Closing...\n");
}

RuntimeEvent Runtime::SubscribeFunction(RuntimeEventCallbackFn callbackfn)
{
    RuntimeEvent event = {
        .uid = ++nextCallbackFnUID,
        .callback = callbackfn,
    };

    events.push_back(event);

    return event;
}
