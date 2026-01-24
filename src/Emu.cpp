#include "Emu.h"

Emu::Emu(): io(), bus(), timer(io), cpu(&bus), cart(){
	cpu.addListener([this]() {timer.tick(); });
}