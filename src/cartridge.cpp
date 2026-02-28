#include "cartridge.h"

uint8_t Cartridge::read(uint16_t addr) {
	if (addr < 0x8000) {
		if (addr < romSize) {
			return ROM[addr - 0x0000];
		}
	}
	else {
		return RAM[addr - 0xA000];
	}
	return 0x00;
}

void Cartridge::write(uint16_t addr, uint8_t val) {
	if (addr >= 0xA000 && addr <= 0xBFFF) {
        RAM[addr - 0xA000] = val;
	}
	else {
		// later mbc
	}
}

bool Cartridge::loadGame(const std::string& fname) {
	std::ifstream gbfile(fname, std::ios::binary);
	if (!gbfile.is_open()) {
		return false;
	}

	gbfile.seekg(0, std::ios::end);
	uintmax_t fileSize = gbfile.tellg();
	gbfile.seekg(0, std::ios::beg);

	constexpr size_t ADDR_SPACE = 0x8000;

	ROM.resize(fileSize);
	romSize = fileSize;
	gbfile.read(reinterpret_cast<char*>(ROM.data()), fileSize);

	RAM.resize((8 * 1024));

	gbfile.close();

	return true;
}