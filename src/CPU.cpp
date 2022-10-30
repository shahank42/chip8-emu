#include "../include/CPU.h"
#include "../include/Opcodes.h"




namespace CHIP8
{

/**
 * Loads a fontset into a vector buffer.
 * 
 * @tparam  T The type of value held by the ROMBuffer.
 * @param   ROMBuffer The buffer to load the fontset to, passed by reference.
 * 
 * @return  A boolean flag indicating whether the fontset was successfully loaded or not.
 */
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

/**
 * Loads a ROM into a vector buffer.
 * 
 * @tparam  T The type of value held by the ROMBuffer.
 * @param   ROMPath The filesystem path of the ROM file.
 * @param   ROMBuffer ROMBuffer The buffer to load the fontset to, passed by reference.
 * 
 * @return  A boolean flag indicating whether the ROM was successfully loaded or not.
 */
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
		ROMBuffer[0x200 + counter] = static_cast<uint8_t>(byteBuffer[0]);
	}
	
	ROMFile.close();
	return true;
}


CPU::CPU(std::string _ROMLocation) : m_ROMLocation { _ROMLocation } { /* ctor */ }

CPU::~CPU() { /* dtor */ }

void CPU::resetRegisters()
{
	m_currentOpcode = 0;

	std::fill(m_memory.begin(), m_memory.end(), 0);
	std::fill(m_registers.V.begin(), m_registers.V.end(), 0);
	std::fill(m_stack.begin(), m_stack.end(), 0);
	std::fill(m_keypad.begin(), m_keypad.end(), 0);

	m_registers.index = 0;
	m_registers.programCounter = 0x200;
	m_registers.delayTimer = 0;
	m_registers.soundTimer = 0;
	m_registers.stackPointer = 0;
}

void CPU::init()
{
	resetRegisters();

	if (!loadFontset(m_memory))
	{
		printf("Error in loading the fontset.\n");
	}

	if (!loadROM(m_ROMLocation, m_memory))
	{
		printf("Error in loading the ROM.\n");
	}
}

void CPU::cycle()
{
	m_currentOpcode = fetchOpcode();
	pointToNextInstruction();

	if (!decodeAndExecuteInstruction())
	{
		printf("UNKWN OP: %x, moved on.\n", m_currentOpcode);
	}
}

}