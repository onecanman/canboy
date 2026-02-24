#pragma once
#include <cstdint>
#include "io.h"

class PPU {
public:
	PPU(IO& io) : io(io) { io.setSTATMode(mode); }
	void tick();
private:
	IO& io;
	int dotcount = 0;
	uint8_t ly = 0;
	uint8_t mode = 2;
	bool prevMatch = false;
	bool bit7Prev = true;
	bool bit7 = true;
};