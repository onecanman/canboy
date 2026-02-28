#pragma once
#include <cstdint>
#include <array>
#include <deque>
#include "io.h"

class PPU {
public:
	PPU(IO& io) : io(io) { io.setSTATMode(mode); }
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
	bool frameReady = false;
	uint8_t fdotcounter;
	uint8_t tileNo;
	uint16_t tileBase;
	uint8_t tileRow;
	uint8_t tileLow;
	uint8_t tileHigh;
	uint8_t fetcherX;
	uint8_t pixelSkip;
	bool wActive = false;
	bool wUsed = false;
	uint8_t wLine = 0;
	std::deque<uint8_t> bgFIFO;
	void enterMode3();
	void tickFetcher();

public:
	const std::array<uint8_t, 160 * 144>& getFrameBuffer() const;
	bool isFrameReady();
	void clrFrameFlag();
	void tick();
};