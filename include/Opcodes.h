#ifndef OPCODES_H
#define OPCODES_H

namespace {

void DBG(const char* str, ...)
{
#ifdef DEBUG_PRINT
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
	uint16_t addr { static_cast<uint8_t>(m_currentOpcode & 0x0FFF) };
	uint8_t x { static_cast<uint8_t>((m_currentOpcode & 0x0F00) >> 8) };
	uint8_t y { static_cast<uint8_t>((m_currentOpcode & 0x00F0) >> 4) };
	uint8_t val { static_cast<uint8_t>(m_currentOpcode & 0x00FF) };
	uint8_t n { static_cast<uint8_t>(m_currentOpcode & 0x000F) };

	switch (m_currentOpcode & 0xF000)
	{
	case 0x0000:
		switch (m_currentOpcode)
		{
		case 0x00E0:
			for (int i { 0 }; i < 32; ++i)
				for (int j { 0 }; j < 64; ++j)
					m_screenData[i][j] = 0;

			DBG("CLS\n");
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

	case 0xD000:
		uint8_t Vx { m_registers.V[x] };
		uint8_t Vy { m_registers.V[y] };
		uint8_t height { n };

		uint8_t posX { static_cast<uint8_t>(Vx % 64) };
		uint8_t posY { static_cast<uint8_t>(Vy % 32) };

		m_registers.V[0xF] = 0;

		for (uint8_t row { 0 }; row < height; ++row)
		{
			int spriteByte { m_memory[m_registers.index + row] };

			for (int col { 0 }; col < 8; ++col)
			{
				if (spriteByte & (0x80 >> col))
				{
					if (m_screenData[posY + row][posX + col] == 0xFFFFFFFF)
						m_registers.V[0xF] = 1;

					m_screenData[posY + row][posX + col] ^= 0xFFFFFFFF;
				}
			}
		}

		DBG("DRW at (%d, %d) for %d bytes.\n", posX, posY, n);
		return true;
		break;
	}
	
	return false;
}

}

#endif