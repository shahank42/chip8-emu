#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

#include <cstdio>

namespace CHIP8 
{

class CPU 
{
public:
	CPU(std::string _ROMLocation);
	~CPU();

	/**
	 * Initializes the CHIP-8 CPU for a first-time run.
	 * 
	 * It involves four steps:
	 *	- resetting all the registers
	 *  - loading the fontset into memory
	 *  - loading the ROM data into memory
	 *  - building the instruction lookup table
	 */
	void init();

	/**
	 * Resets all the registers to their default values.
	 * 
	 * Note that the program counter starts reading from address 0x200.
	 */
	void resetRegisters();

	/**
	 * Builds an instruction lookup table for EACH AND EVERY possible opcode.
	 * This helps in the quick "fetching" of instructions.
	 * 
	 * As heavy as it may sound, it's fine because this function only needs to
	 * be invoked once -- during the initialization phase when the application
	 * is launched.
	 */
	void buildInstructionTable();

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

	using instruction_t = std::function<void(void)>;
	std::unordered_map<uint16_t, instruction_t> m_instructionTable {};

	uint16_t m_currentOpcode { };

	Registers m_registers { };
	std::vector<uint8_t> m_memory { std::vector<uint8_t>(4096, 0) };
	std::vector<uint16_t> m_stack { std::vector<uint16_t>(16, 0) };

	std::vector<uint8_t> m_keypad { std::vector<uint8_t>(16, 0) };

	// Sets the PC to point at the next instruction in memory.
	void nextInstruction() { m_registers.programCounter += 2; }

	// Sets the PC to skip the next instruction in memory, and point to the one after it.
	void skipInstruction() { m_registers.programCounter += 4; }


	// TODO: Update this documentation
	// ~~Here lie the different opcodes the CHIP-8 virtual CPU supports~~
	CPU::instruction_t OP_JMP(uint16_t addr);
	CPU::instruction_t OP_CALL(uint16_t addr);
};

}

#endif
