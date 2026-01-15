#pragma once
#include "Bus.h"
#include "lr35902.h"

class Emu {
public:
	Emu();

	Bus bus;
	lr35902 cpu;
};