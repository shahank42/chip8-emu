#include <iostream>

#include "include/CPU.h"

int main()
{
	CHIP8::CPU chip8 { "F:\\code\\c++\\chip8-emu\\roms\\ibm.ch8" };
	chip8.init();

	return 0; 
}