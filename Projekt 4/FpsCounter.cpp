#include "FpsCounter.h"

#include <GL/glfw.h>
#include <iostream>

// A simple rounding function
template<typename T>
const int round(T x) {
	return static_cast<int>(x + 0.5);
}

FpsCounter::FpsCounter() : oldTime(glfwGetTime()), frameCounter(0) {
}

// Should be called for every frame
void FpsCounter::tick() {
	++frameCounter;
	if (frameCounter < 10) {
		return;
	}

	double currentTime = glfwGetTime();
	timeDelta = currentTime - oldTime;
	if (timeDelta > 1.0) {
		printFps();
		// Reset state
		oldTime = currentTime;
		frameCounter = 0;
	}
}

// Calculates and prints frames per second
const void FpsCounter::printFps() {
	double fps = frameCounter / timeDelta;
	std::cout << round(fps) << " fps" << std::endl;
}