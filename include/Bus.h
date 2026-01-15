#pragma once
#include "lr35902.h"
#include <array>
#include <cstdint>

class Bus {
public:
  Bus();
  ~Bus();

public: 
  std::array<uint8_t, 64 * 1024> ram;

public:
  void write(uint16_t addr, uint8_t data);
  uint8_t read(uint16_t addr);
};
