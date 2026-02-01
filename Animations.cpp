#include "main.h"

void SlideAnim::Restart()
{
	t0 = std::chrono::steady_clock::now();
}

int SlideAnim::OffsetPx() const
{
	using namespace std::chrono;
	float ms = duration<float, std::milli>(std::chrono::steady_clock::now() - t0).count();

	/*
	
	Formula:
		offset = -A * 1/2 * (1 - T/t * 2 * PI)

	English:
		amplitude_px = size of movement in pixels
		T = full period
		T/t = how much of the period has passed (rotation)
		2PI = a full cosine rotation

	Hebrew:
		amplitude_px = גודל התנועה בפיקסלים
		T = מחזור שלם
		T/t = כמה חלק מהמחזור עבר (סיבוב)
		2PI = סיבוב מלא של קוסינוס

	*/

	float cycles = ms / period_ms;
	float off = (float)(amplitude_px * 0.5f * (1.0f - std::cos(cycles * (M_PI * 2))));
	int result = static_cast<int>(std::lround(off));

	return result;
}