#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iterator>
#include <string>
#include <vector>

#define DEBUG
#include <cstdarg>
#include <cstdio>


namespace CHIP8 
{

class CPU 
{
public:
	/**
	 * Basic constructor function for the CHIP8::CPU class.
	 * 
	 * @param _ROMLocation Give the filesystem path of the ROM file.
	 */
	CPU(std::string _ROMLocation);

	/**
	 * Basic destructor function for the CHIP8::CPU class.
	 */
	~CPU();

	/**
	 * Initializes the CHIP-8 CPU for a first-time run.
	 * 
	 * It involves three steps:
	 *	- resetting all the registers
	 *  - loading the fontset into memory
	 *  - loading the ROM data into memory
	 */
	void init();

	/**
	 * Resets all the registers to their default values.
	 * Note that the program counter starts reading from address 0x200.
	 */
	void resetRegisters();

	/**
	 * Decodes the fetched opcode and executes the associated instruction.
	 * 
	 * This is essentially a giant nested switch statement with different branches
	 * according to the opcode's data. 
	 * 
	 * @return A boolean flag indicating whether the "decode and execute" action was successfully carried out or not.
	 */
	bool decodeAndExecuteInstruction();

	/**
	 * Handles all the events taking place during a single cycle of the CHIP-8 CPU.
	 * 
	 * This function is the heart of the entire application, and very rightly is
	 * the reason why it runs. It looks after the entire "fetch, decode and execute" processes
	 * of a typical CPU.
	 */
	void cycle();

private:
	struct Registers
	{
		std::vector<uint8_t> V { std::vector<uint8_t>(16, 0) };
		uint8_t delayTimer { };
		uint8_t soundTimer { };
		uint16_t index { };
		uint16_t programCounter { };
		uint16_t stackPointer { };
	};

	std::string m_ROMLocation { "" };

	uint16_t m_currentOpcode { };

	Registers m_registers { };
	std::vector<uint8_t> m_memory { std::vector<uint8_t>(4096, 0) };
	std::vector<uint16_t> m_stack { std::vector<uint16_t>(16, 0) };
	std::vector<uint16_t> m_frameBuffer { std::vector<uint16_t>(64 * 32, 0) };
	std::vector<uint8_t> m_keypad { std::vector<uint8_t>(16, 0) };


	// Fetches the next opcode from memory, a combination of the two succeeding instructions from the PC.
	uint16_t fetchOpcode() { return ((m_memory[m_registers.programCounter] << 8) | m_memory[m_registers.programCounter + 1]); }

	// Sets the PC to point at the next instruction in memory.
	void pointToNextInstruction() { m_registers.programCounter += 2; }
};

}

#endif
