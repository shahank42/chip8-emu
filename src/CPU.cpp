#include "../include/CPU.h"

namespace CHIP8
{

void loadROM(const std::string& ROMPath)
{
	std::cout << "Loading ROM " << ROMPath << "\n";
}

CPU::CPU(std::string _ROMLocation) 
	: m_ROMLocation { _ROMLocation }
{
	// ctor
}

CPU::~CPU()
{
	// dtor
}

void CPU::init()
{
	loadROM(m_ROMLocation);
}

}