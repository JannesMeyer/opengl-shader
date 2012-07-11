#pragma once

/*
 * Calculates frames per second
 */
class FpsCounter
{
private:
	double oldTime;
	double timeDelta;
	int frameCounter;

public:
	FpsCounter();
	void tick();
	const void printFps();
};
