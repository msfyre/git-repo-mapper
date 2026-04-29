#include "runtime.h"
#include <SDL3/SDL_events.h>
#include <chrono>
#include <cstdio>
#include <vector>

Runtime::Runtime() {
	DeltaTime = 0;
	isRunning = false;
}

void Runtime::Execute() {
	auto prevtime = std::chrono::high_resolution_clock::now();

	isRunning = true;

	while (isRunning) {
		auto currtime = std::chrono::high_resolution_clock::now();

		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				isRunning = false;
			}
		}

		for (auto& callback : events) {
			callback(DeltaTime);
		}

		std::chrono::duration<float> delayduration = currtime - prevtime;

		DeltaTime = delayduration.count();

		prevtime = currtime;
	}

	std::printf("Closing...\n");
}

void Runtime::SubscribeToRuntime(RuntimeEventCallbackFn callbackfn) {
	events.insert(events.begin(), callbackfn);
	std::printf("Subscribed!\n");
}
