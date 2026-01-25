#include "io.h"

IO::IO() {
	IF = 0;
	JOYP = 0xFF;
	TIMA = 0;
	TMA = 0;
	TAC = 0;
	DIV = 0;
}

IO::~IO() {};

uint8_t IO::read(uint16_t addr) {
	switch (addr) {
	case 0xFF0F: return (IF | 0xE0); break;
	case 0xFF00: return JOYP; break;
	case 0xFF04: return DIV; break;
	case 0xFF05: return TIMA; break;
	case 0xFF06: return TMA; break;
	case 0xFF07: return TAC; break;
	default: return 0xFF;
	}
}

void IO::write(uint16_t addr, uint8_t val) {
	switch (addr) {
	case 0xFF0F:
		IF &= (val | 0xE0); 
		break;
	case 0xFF00:
		JOYP = val;
		break;
	case 0xFF04:
		divWrite = true;
		break;
	case 0xFF05:
	    TIMA = val;
		break;
	case 0xFF06:
		TMA = val;
		break;
	case 0xFF07:
		TAC = (val & 0x07);
		break;
	default:
		break;
	}
}

void IO::reqINT(INT type) {
	IF |= (1 << static_cast<int>(type));
}

uint8_t IO::readTIMA() {
	return TIMA;
}

void IO::setTIMA(uint8_t val) {
	TIMA = val;
}

uint8_t IO::readTMA() {
	return TMA;
}

uint8_t IO::readTAC() {
	return TAC;
}

void IO::setDIV(uint8_t val) {
	DIV = val;
}
