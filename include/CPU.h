#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include <cstdio>

namespace CHIP8 
{

class CPU 
{
public:
	CPU(std::string _ROMLocation);
	~CPU();

	void init();

private:
	std::string m_ROMLocation { };

	uint16_t m_currentOpcode { };
	std::vector<uint8_t> m_memory { std::vector<uint8_t>(4096, 0) };

};

}

#endif
