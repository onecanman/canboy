#include "Emu.h"
#include <iostream>
Emu::Emu(): io(), bus(), timer(io), cpu(&bus), cart(), ppu(io, &bus){
	cpu.addListener([this]() {timer.tick(); });
	cpu.addListener([this]() {ppu.tick(); });
}


bool Emu::init() {
	if (!bus.loadBootRom("../../../boot/dmg_boot.bin")) {
		std::cerr << "Failed to load boot ROM\n";
		return false;
	}
	if (!r.init("CanBoy", 4)) {
		return false;
	}

	return true;
}

void Emu::run() {
	int debugCount = 0;
	while (!ppu.isFrameReady()) {
		cpu.clock();
	}
	ppu.clrFrameFlag();
	r.render(ppu.getFrameBuffer());
	r.procEvents();
}

