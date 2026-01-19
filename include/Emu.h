#pragma once
#include "Bus.h"
#include "lr35902.h"
#include "cartridge.h"

class Emu {
public:
	Emu();

	Bus bus;
	lr35902 cpu;
	Cartridge cart;
};