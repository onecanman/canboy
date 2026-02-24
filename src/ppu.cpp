#include "ppu.h"

void PPU::tick() {
	dotcount++;
	if (dotcount == 456) {
		dotcount = 0;
		uint8_t prevLY = ly;
		ly++;
		if (ly == 154) {
			ly = 0;
		}
		io.setLY(ly);
		io.setSTATFlag(ly == io.readLYC());
		if (prevLY == 143 && ly == 144) {
			io.reqINT(IO::INT::VBlank);
		}
	}
	if (ly <= 143) {
		if (dotcount < 80) mode = 2;
		else if (dotcount < 252) mode = 3;
		else mode = 0;
	} else {
		mode = 1;
	}
	io.setSTATMode(mode);
}