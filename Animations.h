#pragma once
#include <chrono>
#include <cmath>

struct SlideAnim
{
	float amplitude_px;
	float period_ms;
	std::chrono::steady_clock::time_point t0;

	SlideAnim(float amp = 5.0f, float period = 600.0f) : amplitude_px(amp), period_ms(period), t0(std::chrono::steady_clock::now()) {}

	void Restart();
	int OffsetPx() const;
};