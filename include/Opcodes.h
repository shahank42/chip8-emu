#ifndef OPCODES_H
#define OPCODES_H

namespace CHIP8
{

CPU::instruction_t CPU::OP_JMP(uint16_t addr)
{
	return [this, addr]() {
		m_registers.programCounter = addr;
	};
}

CPU::instruction_t CPU::OP_CALL(uint16_t addr)
{
	return [this, addr]() {
		m_stack[m_registers.stackPointer++] = m_registers.programCounter;
		m_registers.programCounter = addr;
	};
}

}

#endif
