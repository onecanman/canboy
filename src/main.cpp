#include "Emu.h"
#include <iostream>

int main() {
    Emu gb;


    gb.cpu.regs.pc = 0x0000;
    gb.cpu.regs.sp = 0xFFFE;
    gb.cart.loadGame("../../../src/test.gb");
    gb.bus.attachCart(&gb.cart);
    
    std::cout << "PC before clock = "
        << std::hex << gb.cpu.regs.pc << "\n";


    while (!gb.cpu.isHalted()) {
        uint16_t pc = gb.cpu.regs.pc;
        uint8_t op = gb.bus.read(pc);

        std::cout << "PC=" << std::hex << pc
            << " OP=" << (int)op << "\n";

        gb.cpu.clock();

        static int stepCount = 0;
        if ((++stepCount % 1000) == 0) {
            uint8_t div = gb.bus.read(0xFF04);
            uint8_t tima = gb.bus.read(0xFF05);
            uint8_t ifr = gb.bus.read(0xFF0F);

            std::cout << std::hex
                << "STEP=" << stepCount
                << " DIV=" << (int)div
                << " TIMA=" << (int)tima
                << " IF=" << (int)ifr
                << "\n";
        }
    }

    auto& r = gb.cpu.regs;

    std::cout << std::hex;
    std::cout << " CPU STATE\n";
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

    std::cout << "\n MEMORY DUMP \n";

    uint8_t mIE = gb.bus.read(0xFFFF);
    uint8_t mIF = gb.bus.read(0xFF0F);
    std::cout << std::hex;
    std::cout << "IE = " << (int)mIE << "\n";
    std::cout << "IF = " << (int)mIF << "\n";

    return 0;   
}