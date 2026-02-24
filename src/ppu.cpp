#include "ppu.h"

void PPU::tick() {
	uint8_t lcdc = io.readLCDC();
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

	bool currentMatch = (ly == io.readLYC());
	io.setSTATFlag(currentMatch);
	uint8_t stat = io.readSTAT();
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
	stat = io.readSTAT();
	if (mode != prevMode) {
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
	prevMatch = currentMatch;
	bit7Prev = bit7;
}