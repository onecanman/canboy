#include "Bus.h"
#include "cartridge.h"

Bus::Bus() {
  for (auto &i : WRAM)
      i = 0x00;
  for (auto& i : HRAM)
      i = 0x00;
  for (auto& i : IO)
      i = 0x00;
  IE = 0x00;
}

Bus::~Bus() {}

void Bus::write(uint16_t addr, uint8_t data) {
  if (addr >= 0x0000 && addr <= 0xFFFF) {
    ram[addr] = data;
  }
}

uint8_t Bus::read(uint16_t addr) {
    if (addr >= 0x0000 && addr <= 0x7FFF) return cart->read(addr); // rom
    else if (addr >= 0x8000 && addr <= 0x9FFF) return VRAM[addr - 0x8000]; // vram
    else if (addr >= 0xA000 && addr <= 0xBFFF) return cart->read(addr); // ram
    else if (addr >= 0xC000 && addr <= 0xDFFF) return WRAM[addr - 0xC000]; // wram
    else if (addr >= 0xE000 && addr <= 0xFDFF) return WRAM[addr - 0xE000]; // echo ram
    else if (addr >= 0xFE00 && addr <= 0xFE9F) return OAM[addr - 0xFE00]; // oam
    else if (addr >= 0xFEA0 && addr <= 0xFEFF) return 0xFF; // not usable
    else if (addr >= 0xFF00 && addr <= 0xFF7F) return IO[addr - 0xFF00]; // io
    else if (addr >= 0xFF80 && addr <= 0xFFFE) return HRAM[addr - 0xFF80]; // hram
    else if (addr == 0xFFFF) return IE;
    else return 0xFF;
}

void Bus::attachCart(Cartridge* c) {
    cart = c;
}