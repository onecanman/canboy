#include "lr35902.h"
#include "Bus.h"
#include <iostream>

using cpu = lr35902;

cpu::lr35902(Bus *b) : bus(b){
  instSet = new instructionSet(this);
  r8[0] = &regs.b;
  r8[1] = &regs.c;
  r8[2] = &regs.d;
  r8[3] = &regs.e;
  r8[4] = &regs.h;
  r8[5] = &regs.l;
  r8[6] = nullptr; 
  r8[7] = &regs.a;
    
  r16[0] = &regs.bc;
  r16[1] = &regs.de;
  r16[2] = &regs.hl;
  r16[3] = &regs.sp;
}
cpu::~lr35902() { delete instSet; }

uint8_t cpu::fetch() {
  fetched = read(regs.pc);
  regs.pc++;
  return fetched;
}

uint8_t cpu::read(uint16_t a) { return bus->read(a); }

void cpu::write(uint16_t a, uint8_t d) { bus->write(a, d); }

void cpu::reset() {
  regs = Registers{};
  fetched = 0x00;
  opcode = 0x00;
  cycles = 0;
  HALT = false;
  STOP = false;
  IME = false;
  IMEPending = false;
}

void cpu::clock() {
  if (HALT) {
    uint8_t IF = read(0xFF0F);
    if (IF != 0) {
      HALT = false;
    }
    return;
  }

  if (serviceINT())
      return;


  if (cycles == 0) {
    opcode = fetch();
    exec(opcode);
  }

  if (cycles > 0) cycles--;

  if (IMEPending) {
    IME = true;
    IMEPending = false;
  }
}

void cpu::exec(uint8_t opcode) {
  cycles = instSet->tstates[opcode];
  instSet->decode(opcode);
}

bool cpu::serviceINT() {
  if (!IME) {
    return false;
  }
  uint8_t IE = read(0xFFFF);
  uint8_t IF = read(0xFF0F);
  if ((IE & IF) == 0) {
    return false;
  }
  IME = false;
  HALT = false;
  uint8_t pending = IE & IF;
  if (pending & 1) {
    // vblank
    write(0xFF0F, IF &= ~(1));
    instSet->push(regs.pc);
    regs.pc = 0x0040;
  } else if ((pending >> 1) & 1) {
    // lcd
    write(0xFF0F, IF &= ~(1 << 1));
    instSet->push(regs.pc);
    regs.pc = 0x0048;
  } else if ((pending >> 2) & 1) {
    // timer
    write(0xFF0F, IF &= ~(1 << 2));
    instSet->push(regs.pc);
    regs.pc = 0x0050;
  } else if ((pending >> 3) & 1) {
    // serial
    write(0xFF0F, IF &= ~(1 << 3));
    regs.pc = 0x0058;
    instSet->push(regs.pc);
  } else if ((pending >> 4) & 1) {
    // joypad
    write(0xFF0F, IF &= ~(1 << 4));
    instSet->push(regs.pc);
    regs.pc = 0x0060;
  } else {
    return false;
  }
  return true;
}
