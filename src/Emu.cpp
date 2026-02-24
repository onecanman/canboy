#include "Emu.h"

Emu::Emu(): io(), bus(), timer(io), cpu(&bus), cart(), ppu(io){
	cpu.addListener([this]() {timer.tick(); });
	cpu.addListener([this]() {ppu.tick(); });
}