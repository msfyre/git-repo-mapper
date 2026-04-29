#include "runtime.h"
#include <SDL3/SDL_events.h>
#include <chrono>
#include <cstdio>

void execute_runtime() {
	Runtime runtime;
	runtime.isRunning = true;

	float deltatime = 0;

	auto prevtime = std::chrono::high_resolution_clock::now();

	while (runtime.isRunning) {
		auto currtime = std::chrono::high_resolution_clock::now();

		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				runtime.isRunning = false;
			}
		}

		std::chrono::duration<float> delayduration = currtime - prevtime;

		deltatime = delayduration.count();

		prevtime = currtime;

		std::printf("%f ms\n", deltatime);
	}

	std::printf("Calling it quits...");
}
