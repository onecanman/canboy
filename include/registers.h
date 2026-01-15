#pragma once
#include <cstdint>

class Registers {
public:
  Registers() {
    pc = 0x0000;
    sp = 0x0000;
    af = 0x0000;
    bc = 0x0000;
    de = 0x0000;
    hl = 0x0000;
  }

public:
  enum FLAGS {
    Z = (1 << 7), // zero
    N = (1 << 6), // subtract
    H = (1 << 5), // half carry
    C = (1 << 4), // carry
  };

  uint16_t pc = 0x00; // program counter
  uint16_t sp = 0x00; // stack pointer

  union {
    struct {
      uint8_t a, f; // accumulator and flag
    };
    uint16_t af;
  };
  union {
    struct {
      uint8_t b, c;
    };
    uint16_t bc;
  };
  union {
    struct {
      uint8_t d, e;
    };
    uint16_t de;
  };
  union {
    struct {
      uint8_t h, l;
    };
    uint16_t hl;
  };

  void setFlag(FLAGS flag, bool state);
  bool checkFlag(FLAGS flag);
};
