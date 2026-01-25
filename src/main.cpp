#include "Emu.h"
#include <iostream>
#include <fstream>
#include <filesystem>

void loadTest(Emu& gb, const char* path, uint16_t base);

int main() {
    Emu gb;

    
  gb.bus.write(0x0000, 0xC9);
  loadTest(gb, "../../../src/test.bin", 0xC000);

  gb.cpu.regs.pc = 0xC000;
  gb.cpu.regs.sp = 0xCFFF;

  std::cout << "PC before clock = "
      << std::hex << gb.cpu.regs.pc << "\n";


  while (!gb.cpu.isHalted()) {
      gb.cpu.step();
  } 

  auto& r = gb.cpu.regs;

  std::cout << std::hex;
  std::cout << "==== CPU STATE ====\n";
  std::cout << "is halted or not" << (int)gb.cpu.isHalted() << std::endl;
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
  std::cout << "BC=" << (int)r.bc << " DE=" << (int)r.de << "\n";
  std::cout << "HL=" << (int)r.hl << " SP=" << (int)r.sp << "\n";

  std::cout << "\n==== MEMORY DUMP ====\n";

  uint8_t mIE = gb.bus.read(0xFFFF);
  uint8_t mIF = gb.bus.read(0xFF0F);

  std::cout << std::hex;
  std::cout << "IE = " << (int)mIE << "\n";
  std::cout << "IF = " << (int)mIF << "\n";
  std::cout << "c100" << (int)gb.bus.read(0xc100) << std::endl;
  std::cout << "c101" << (int)gb.bus.read(0xc101) << std::endl;
  std::cout << "c102" << (int)gb.bus.read(0xc102) << std::endl;
  std::cout << "c103" << (int)gb.bus.read(0xc103) << std::endl;


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