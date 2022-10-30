#include "../include/CPU.h"

namespace CHIP8
{

template <typename T>
bool loadFontset(std::vector<T>& ROMBuffer)
{
	const std::vector<uint8_t> fontset
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

	for (long i { 0 }; i < fontset.size(); ++i)
		ROMBuffer[0x50 + i] = fontset[i];

	return true;
}

template <typename T>
bool loadROM(const std::string& ROMPath, std::vector<T>& ROMBuffer)
{
	std::ifstream ROMFile(ROMPath, std::fstream::binary);

	if (!ROMFile.is_open())
	{
		printf("This ROM (%s) is invalid.\n", ROMPath.c_str());
		return false;
	}
	
	char byteBuffer[1];
	
	for (int counter { 0 }; !ROMFile.eof(); ++counter)
	{
		ROMFile.read(byteBuffer, 1);
		ROMBuffer[0x200 + counter] = byteBuffer[0];
	}
	
	ROMFile.close();

	return true;
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
	// Reset registers

	if (!loadFontset(m_memory))
	{
		printf("Error in loading the fontset.\n");
	}

	if (!loadROM(m_ROMLocation, m_memory))
	{
		printf("Error in loading the ROM.\n");
	}

	// Build the instruction table
}

}