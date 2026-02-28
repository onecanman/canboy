#include "ppu.h"

void PPU::tick() {
	uint8_t lcdc = io.read(IO::REG::LCDC);
	bit7 = lcdc & 0x80;
	if (bit7Prev && !bit7) {
		dotcount = 0;
		ly = 0;
		mode = 0;
		io.setLY(0);
		io.setSTATMode(0);
		prevMatch = false;
	}
	if (!bit7Prev && bit7) {
		dotcount = 0;
		ly = 0;
		mode = 2;
		io.setLY(0);
		io.setSTATMode(2);
		prevMatch = false;
	}
	if (!bit7) {
		bit7Prev = bit7;
		return;
	}
	dotcount++;
	if (dotcount == 456) {
		dotcount = 0;
		uint8_t prevLY = ly;
		ly++;
		if (ly == 154) {
			ly = 0;
		}
		io.setLY(ly);
		if (prevLY == 143 && ly == 144) {
			io.reqINT(IO::INT::VBlank);
		}
	}

	bool currentMatch = (ly == io.read(IO::REG::LYC));
	io.setSTATFlag(currentMatch);
	uint8_t stat = io.read(IO::REG::STAT);
	if (!prevMatch && currentMatch) {
		if (stat & 0x40) {
			io.reqINT(IO::INT::LCDStat);
		}
	}

	uint8_t prevMode = mode;
	if (ly <= 143) {
		if (dotcount < 80) mode = 2;
		else if (dotcount < 252) mode = 3;
		else mode = 0;
	} else {
		mode = 1;
	}
	io.setSTATMode(mode);
	stat = io.read(IO::REG::STAT);
	if (mode != prevMode) {
		if (prevMode == 2 && mode == 3) {
			enterMode3();
		}
		// INT
		if (mode == 0) {
			if (stat & 0x08) {
				io.reqINT(IO::INT::LCDStat);
			}
		}
		else if (mode == 1) {
			if (stat & 0x10) {
				io.reqINT(IO::INT::LCDStat);
			}
		}
		else if (mode == 2) {
			if (stat & 0x20) {
				io.reqINT(IO::INT::LCDStat);
			}
		}
	}
	if (mode == 3 && ly <= 143) {
		tickFetcher();
		if (!bgFIFO.empty() && xPixel < 160) {
			uint8_t color = bgFIFO.front();
			bgFIFO.pop_front();
			if (pixelSkip > 0) {
				pixelSkip--;
			}
			else {
				if (io.read(IO::REG::LCDC) & 0x01) {
					framebuffer[ly * 160 + xPixel] = color;
				}
				else {
					framebuffer[ly * 160 + xPixel] = 0;
				}
				xPixel++;
			}
		}
	}
	prevMatch = currentMatch;
	bit7Prev = bit7;
}


const std::array<uint8_t, 160 * 144>& PPU::getFrameBuffer() const {
	return framebuffer;
}

void PPU::enterMode3() {
	bgFIFO.clear();
	state = FState::getTile;
	fdotcounter = 0;
	fetcherX = 0;
	xPixel = 0;
	uint8_t scx = io.read(IO::REG::SCX);
	pixelSkip = scx & 7;
}

void PPU::tickFetcher() {
	switch (state) {
	case FState::getTile:
		fdotcounter++;
		if (fdotcounter == 2) {
			fdotcounter = 0;
			uint8_t scx = io.read(IO::REG::SCX);
			uint8_t scy = io.read(IO::REG::SCY);
			uint8_t lcdc = io.read(IO::REG::LCDC);
			uint8_t bgY = (scy + ly) & 0xFF;
			uint8_t tileY = bgY / 8;
			uint8_t tileX = ((scx / 8) + fetcherX) & 31; 
			uint16_t tileMapBase = (lcdc & 0x08) ? 0x9C00 : 0x9800;
			uint16_t addr = tileMapBase + (tileY * 32 + tileX);
			tileNo = io.read(addr);
			state = FState::getLow;
		}
		break;
	case FState::getLow:
		fdotcounter++;
		if (fdotcounter == 2) {
			fdotcounter = 0;
			uint8_t scy = io.read(IO::REG::SCY);
			uint8_t bgY = (scy + ly) & 0xFF;
			tileRow = bgY & 0x07;
			uint8_t lcdc = io.read(IO::REG::LCDC);
			tileBase = (lcdc & 0x10) ? (0x8000 + tileNo * 16) : (0x9000 + static_cast<int8_t>(tileNo) * 16);
			tileLow = io.read(tileBase + tileRow * 2);
			state = FState::getHigh;
		}
		break;
	case FState::getHigh:
		fdotcounter++;
		if (fdotcounter == 2) {
			fdotcounter = 0;
			tileHigh = io.read(tileBase + (tileRow * 2 + 1));
			state = FState::sleep;
		}
		break;
	case FState::sleep:
		fdotcounter++;
		if (fdotcounter == 2) {
			fdotcounter = 0;
			state = FState::push;
		}
		break;
	case FState::push:
		if (bgFIFO.size() <= 8) {
			for (uint8_t i = 0; i < 8; i++) {
				uint8_t lowBit = ((tileLow >> (7 - i)) & 1);
				uint8_t highBit = ((tileHigh >> (7 - i)) & 1);
				uint8_t color = (highBit << 1) | lowBit;
				bgFIFO.push_back(color);
			}
			fetcherX++;
			state = FState::getTile;
		}
		break;
	}
}