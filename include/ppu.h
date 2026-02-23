#pragma once
#include <cstdint>


class PPU {
public:
	void tick();
private:
	int dotcount = 0;
	uint8_t ly = 0;
	uint8_t mode;
};