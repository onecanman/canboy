#pragma once
#include <cstdint>
#include "io.h"

class Timer {
public:
	Timer(IO& i): io(i) {}
	void tick();

private:
	IO& io;
	uint16_t divider {};
	bool prevClockBit = false;
};