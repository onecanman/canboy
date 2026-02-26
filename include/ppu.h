#pragma once
#include <cstdint>
#include <array>
#include <deque>
#include "io.h"

class PPU {
public:
	PPU(IO& io) : io(io) { io.setSTATMode(mode); }
	void tick();
private:
	IO& io;
	std::array<uint8_t, 160 * 144> framebuffer{};
	uint16_t dotcount = 0;
	uint8_t ly = 0;
	uint8_t mode = 2;
	bool prevMatch = false;
	bool bit7Prev = true;
	bool bit7 = true;
	uint8_t xPixel;
	enum class FState {
		getTile,
		getLow,
		getHigh,
		sleep,
		push
	};
	FState state;
	uint8_t fdotcounter;
	uint8_t tileNo;
	uint8_t tileLow;
	uint8_t tileHigh;
	uint8_t fetcherX;
	std::deque<uint8_t> bgFIFO;
	void enterMode3();
	void tickFetcher();

public:
	const std::array<uint8_t, 160 * 144>& getFrameBuffer() const;
};