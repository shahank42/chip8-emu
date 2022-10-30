#ifndef OPCODES_H
#define OPCODES_H

namespace {

	void DBG(const char* str, ...)
	{
#ifdef DEBUG
		va_list arglist;
		va_start(arglist, str);
		vprintf(str, arglist);
		va_end(arglist);
#endif
	}

}

namespace CHIP8
{

bool CPU::decodeAndExecuteInstruction()
{
	uint8_t addr { static_cast<uint8_t>(m_currentOpcode & 0x0FFF) };
	uint8_t x { static_cast<uint8_t>((m_currentOpcode & 0x0F00) >> 8) };
	uint8_t val { static_cast<uint8_t>(m_currentOpcode & 0x00FF) };

	switch ((m_currentOpcode & 0xF000))
	{
	case 0x0000:
		switch (m_currentOpcode)
		{
		case 0x00E0:
			// TODO: Implement a screen, and then clear it.

			DBG("CLS\n");
			return true;
			break;

		case 0x00EE:

			DBG("RET from (addr) 0x%x.\n", m_registers.programCounter);
			return true;
			break;
		}

		break;

	case 0x1000:
		m_registers.programCounter = addr;

		DBG("JMP to (addr) 0x%x.\n", m_registers.programCounter);
		return true;
		break;

	case 0x6000:
		m_registers.V[x] = val;

		DBG("LD (reg) V%x := (val) 0x%x.\n", x, val);
		return true;
		break;

	case 0x7000:
		m_registers.V[x] += val;

		DBG("ADD (reg) V%x += (val) 0x%x.\n", x, val);
		return true;
		break;

	case 0xA000:
		m_registers.index = addr;

		DBG("LD (reg) I := (addr) 0x%x.\n", addr);
		return true;
		break;
	}
	
	return false;
}

}

#endif