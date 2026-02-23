#include "ppu.h"

void PPU::tick() {
	dotcount++;
	if (dotcount == 456) {
		dotcount = 0;
		ly++;
		if (ly == 154) {
			ly = 0;
		}
	}
	if (ly <= 143) {
		if (dotcount < 80) mode = 2;
		else if (dotcount < 252) mode = 3;
		else mode = 0;
	} else {
		mode = 1;
	}
}