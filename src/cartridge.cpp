#include "cartridge.h"

Cartridge::read(uint16_t addr) {
	if (addr < 0x8000) {
		return ROM[addr - 0x0000];
	}
	else {
		return RAM[addr - 0xA000];
	}
}

Cartridge::write(uint16_t addr, uint8_t val) {
	RAM[addr - 0xA000] = val;
}