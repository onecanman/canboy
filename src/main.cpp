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

  std::cout << "PC before clock = "
      << std::hex << gb.cpu.regs.pc << "\n";

  gb.cpu.regs.pc = 0xC000;
  gb.cpu.regs.sp = 0xFFFE;

  gb.bus.write(0xC040, 0x3E); // LD A,42
  gb.bus.write(0xC041, 0x42);
  gb.bus.write(0xC042, 0xC9); // RET

  gb.bus.write(0x0040, 0x3E); // LD A,66
  gb.bus.write(0x0041, 0x66);
  gb.bus.write(0x0042, 0xEA); // LD (C101),A
  gb.bus.write(0x0043, 0x01);
  gb.bus.write(0x0044, 0xC1);
  gb.bus.write(0x0045, 0xD9); // RETI





  while (!gb.cpu.isHalted()) {
      gb.cpu.step();
      std::cout << "is halted or not" << (int)gb.cpu.isHalted() << std::endl;
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
      std::cout << "BC=" << (int)r.bc << " DE=" << (int)r.de << "\n";
      std::cout << "HL=" << (int)r.hl << " SP=" << (int)r.sp << "\n";
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
  std::cout << "BC=" << (int)r.bc << " DE=" << (int)r.de << "\n";
  std::cout << "HL=" << (int)r.hl << " SP=" << (int)r.sp << "\n";

  std::cout << "\n==== MEMORY DUMP ====\n";

  uint8_t m_c100 = gb.bus.read(0xC100);
  uint8_t m_c101 = gb.bus.read(0xC101);

  std::cout << std::hex;
  std::cout << "[0xC100] = " << (int)m_c100 << "\n";
  std::cout << "[0xC101] = " << (int)m_c101 << "\n";
  std::cout << "[0xC102] = " << (int)gb.bus.read(0xC102) << "\n";
  std::cout << "[0xC103] = " << (int)gb.bus.read(0xC103) << "\n";
  std::cout << "[0xC104] = " << (int)gb.bus.read(0xC104) << "\n";


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