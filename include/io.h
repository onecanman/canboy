#pragma once
#include <cstdint>

class IO {
public:
	IO();
	~IO();

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
	// timer functions
	uint8_t readTIMA();
	void setTIMA(uint8_t val);
	uint8_t readTMA();
	uint8_t readTAC();
	void setDIV(uint8_t val);
	bool divWrite = false;
	// ppu functions
	void setLY(uint8_t val);
	uint8_t readLYC();
	uint8_t readSTAT();
	void setSTATMode(uint8_t mode);
	void setSTATFlag(bool match);
	uint8_t readLCDC();

private:
	uint8_t IF;
	uint8_t JOYP;
	uint8_t DIV; 
	uint8_t TIMA;
	uint8_t TMA;
	uint8_t TAC;
	uint8_t LCDC;
	uint8_t STAT;
	uint8_t LY;
	uint8_t LYC;
	uint8_t SCX;
	uint8_t SCY;
	uint8_t WX;
	uint8_t WY;
};