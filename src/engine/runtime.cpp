#include <SDL3/SDL_events.h>
#include <SDL3/SDL_timer.h>

#include <engine/engine.hpp>
#include <engine/runtime.hpp>

#include <chrono>
#include <cstddef>
#include <cstdio>

#include <diagnostics/cpu.hpp>
#include <ncurses.h>

#ifdef __linux__
#include <unistd.h>
#endif

using namespace engine::runtime;

Runtime::Runtime(size_t fps_cap) {
    DeltaTime = 0;
    isRunning = false;
    nextCallbackFnUID = 0;
    frameDelayMS = (1.0 / fps_cap) * 1000;
}

void Runtime::Execute() {
    auto prevtime = std::chrono::high_resolution_clock::now();

    isRunning = true;

    initscr();
    noecho();
    curs_set(FALSE);

    diagnostics::cpu::ProcessMonitor monitor(getpid());

    while (isRunning) {
        SDL_Event sdl_event;

        while (SDL_PollEvent(&sdl_event)) {
            if (sdl_event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
        }

        for (RuntimeEvent event : events) {
            event.callback(DeltaTime, sdl_event);
        }

        auto currtime = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float> delayduration = currtime - prevtime;

        DeltaTime = delayduration.count();

        SDL_Delay(frameDelayMS - DeltaTime);

        diagnostics::cpu::CPUTimes cputimes = diagnostics::cpu::readCPUTimes();

        mvprintw(0, 0, "DEBUG MENU");
        mvprintw(2, 0, "FPS: %f", 1 / DeltaTime);
        mvprintw(3, 0, "CPU USAGE: %f%%", monitor.GetUsagePercentage());

        refresh();

        prevtime = currtime;
    }

    endwin();

    printf("\nClosing...\n");
}

RuntimeEvent Runtime::SubscribeFunction(RuntimeEventCallbackFn callbackfn) {
    RuntimeEvent event = {
        .uid = ++nextCallbackFnUID,
        .callback = callbackfn,
    };

    events.push_back(event);

    return event;
}
