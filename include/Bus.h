#pragma once
#include "lr35902.h"
#include <array>
#include <cstdint>

class Cartridge;
class IO;

class Bus {
public:
	Bus();
	~Bus();

private: 
	Cartridge* cart = nullptr;
	IO* io = nullptr;
  std::array<uint8_t, 0x2000> VRAM; // 8000
  std::array<uint8_t, 0x2000> WRAM{}; // C000
  std::array<uint8_t, 0x00A0> OAM;  // FE00
  std::array<uint8_t, 0x007F> HRAM{}; // FF80
  uint8_t IE{};
  bool dmaActive = false;
  uint16_t dmaSource = 0;
  uint16_t dmaTicks = 0;
  uint8_t dmaIndex = 0;
  void startDMA(uint8_t val);
  void tickDMA();
  bool isDMAActive();

public:
  void write(uint16_t addr, uint8_t data);
  uint8_t read(uint16_t addr);
  uint8_t dmaRead(uint16_t addr);
  void attachCart(Cartridge *c);
  void attachIO(IO* i);
};
