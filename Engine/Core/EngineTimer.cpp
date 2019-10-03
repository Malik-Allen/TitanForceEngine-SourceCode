#include "EngineTimer.h"
#include <iostream>

EngineTimer::EngineTimer():
	prevTicks(0.0f),
	currentTicks(0.0f),
	fps(60){EngineTimer::Reset();}

EngineTimer::~EngineTimer() {}

void EngineTimer::SetFPS(unsigned int fps_) { fps = fps_;}

void EngineTimer::Reset() {
	prevTicks = Timer::GetCurrentTimeInMicroSeconds();
	currentTicks = Timer::GetCurrentTimeInMicroSeconds();
}

void EngineTimer::UpdateFrameTicks() {
	prevTicks = currentTicks;
	currentTicks = Timer::GetCurrentTimeInMicroSeconds();
}

float EngineTimer::GetDeltaTime() const {
	return static_cast<float>(currentTicks - prevTicks) / 1000000.0f;	// Conversion to seconds
}

float EngineTimer::GetSleepTime(const unsigned int fps_) {
	unsigned int milliSecsPerFrame = 1000 / fps_;

	if (milliSecsPerFrame == 0)
		return 0;

	unsigned int sleepTime = milliSecsPerFrame - static_cast<unsigned int>(Timer::GetCurrentTimeInMicroSeconds());

	if (sleepTime > milliSecsPerFrame)
		return milliSecsPerFrame;

	return sleepTime;
}