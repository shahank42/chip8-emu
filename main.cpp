#include <iostream>

#include "include/CPU.h"


void play()
{
	CHIP8::CPU chip8 { "F:\\code\\c++\\chip8-emu\\roms\\ibm.ch8" };
	chip8.init();

	bool quit { false };
	while (!quit)
	{
		chip8.cycle();
	}
}

int main()
{
	try 
	{
		play();
	}
	catch (const std::exception& e)
	{
		std::cerr << "ERROR: " << e.what();
		return 1;
	}

	return 0; 
}