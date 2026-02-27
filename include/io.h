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
	enum class REG : uint16_t {
		LCDC = 0xFF40,
		STAT = 0xFF41,
		SCY = 0xFF42,
		SCX = 0xFF43,
		LY = 0xFF44,
		LYC = 0xFF45,
		WY = 0xFF4A,
		WX = 0xFF4B
	};

	uint8_t read(uint16_t addr);
	uint8_t read(REG r) { return read(static_cast<uint16_t>(r)); }
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
	void setSTATMode(uint8_t mode);
	void setSTATFlag(bool match);

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