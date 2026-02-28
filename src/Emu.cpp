#include "Emu.h"

Emu::Emu(): io(), bus(), timer(io), cpu(&bus), cart(), ppu(io){
	cpu.addListener([this]() {timer.tick(); });
	cpu.addListener([this]() {ppu.tick(); });
}


bool Emu::init() {
	if (!r.init("CanBoy", 4)) {
		return false;
	}

	return true;
}

void Emu::run() {
	cpu.clock();
	if (ppu.isFrameReady()) {


		ppu.clrFrameFlag();
	}
}

