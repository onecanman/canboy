#include "Emu.h"
#include <iostream>
#include <fstream>
#include <filesystem>

void loadTest(Emu& gb, const char* path, uint16_t base);

int main() {
    Emu gb;

  loadTest(gb, "../../../src/test.bin", 0xC000);

  gb.cpu.regs.pc = 0xC000;

  std::cout << "PC before clock = "
      << std::hex << gb.cpu.regs.pc << "\n";

  for (int i = 0; i < 20; i++) {
    gb.cpu.clock();
  }

  auto& r = gb.cpu.regs;

  std::cout << std::hex;
  std::cout << "==== CPU STATE ====\n";
  std::cout << "PC=" << r.pc << " SP=" << r.sp << "\n";

  std::cout << "A=" << (int)r.a << " F=" << (int)r.f
      << "  ["
      << ((r.f & 0x80) ? 'Z' : '-')
      << ((r.f & 0x40) ? 'N' : '-')
      << ((r.f & 0x20) ? 'H' : '-')
      << ((r.f & 0x10) ? 'C' : '-')
      << "]\n";

  std::cout << "B=" << (int)r.b << " C=" << (int)r.c << "\n";
  std::cout << "D=" << (int)r.d << " E=" << (int)r.e << "\n";
  std::cout << "H=" << (int)r.h << " L=" << (int)r.l << "\n";

  return 0;
}


void loadTest(Emu& gb, const char* path, uint16_t base) {
    std::ifstream file(path, std::ios::binary);
    uint8_t byte;
    uint16_t addr = base;

    if (!file.is_open()) {
        std::cerr << "FAILED to open file: " << path << "\n";
        return;
    }

    while (file.read(reinterpret_cast<char*>(&byte), 1)) {
        gb.bus.write(addr++, byte);
    }
}