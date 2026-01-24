#include "timer.h"


void Timer::tick() {
	divider++;
	io.setDIV((divider >> 8));

	uint8_t tacVal = io.readTAC();
	bool timerEnabled = (tacVal >> 2) & 1;
	uint8_t selectBits = tacVal & 3;

	uint8_t clockBit;
	switch (selectBits) {
	case 0b00: clockBit = 9; break;
	case 0b01: clockBit = 3; break;
	case 0b10: clockBit = 5; break;
	case 0b11: clockBit = 7; break;
	}

	bool currentClockBit = (divider >> clockBit) & 1;
	if (prevClockBit == 1 && currentClockBit == 0 && timerEnabled) {
		uint8_t timaVal = io.readTIMA();
		if (timaVal == 0xFF) {
			io.setTIMA(io.readTMA());
			io.reqINT(IO::INT::Timer);
		}
		else {
			timaVal++;
			io.setTIMA(timaVal);
		}
	}

	prevClockBit = currentClockBit;
}