#pragma once
#include <cstdint>

class IO {
	IO();
	~IO();
	uint8_t IF;
	uint8_t JOYP;
	uint8_t DIV;
	uint8_t TIMA;
	uint8_t TMA;
	uint8_t TAC;

public:
	enum class INT {
		VBlank,
		LCDStat,
		Timer,
		Serial,
		Joypad
	};

public:
	uint8_t read(uint16_t addr);
	void write(uint16_t addr, uint8_t val);
	void reqINT(INT type);
};