#pragma once
#define CPU_H
#ifdef CPU_H

#include<string>
#include "ram.h"

class CPU {
private:
	int generalRegisters[20];
	int accumulator;
	int programCounter;
	int memoryAddressRegister;
	std::string memoryDataRegister;
	std::string currentInstructionRegister;
	RAM *ramRef;
public:
	CPU(RAM *ramReference);
	int getAccumulator();
	void runProgramFromRam();
	void loadToAccumulator(int data);
	int getRegisterVal(int id);
	void loadToRegister(int data, int id);
	void performInstruction(std::string instruction);
};

#endif