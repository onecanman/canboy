#pragma once
#include "lr35902.h"
#include <array>
#include <cstdint>

class Bus {
public:
  Bus();
  ~Bus();

public: 
  std::array<uint8_t, 0x2000> VRAM; // 8000
  std::array<uint8_t, 0x2000> WRAM; // C000
  std::array<uint8_t, 0x00A0> OAM;  // FE00
  std::array<uint8_t, 0x007F> HRAM; // FF80
  std::array<uint8_t, 0x80> IO;
  uint8_t IE;

public:
  void write(uint16_t addr, uint8_t data);
  uint8_t read(uint16_t addr);
};
