#include<iostream>
#include<map>
#include "cpu.h"
#include "ram.h"

/*
Commands (X represents any denery number and Y represents some text):
LDAV X [Loads value X into the accumulator]
LDAR X [Loads the value from register X into the accumulator. X cannot be less than 0 or greater than 19.]
INP [Recieves input from the user and sends it to the accumulator.]
ADD X [Adds X to the accumulator]
SUB X [Subtracts X from the accumulator]
MUL X [Multiplies the number in the accumulator by X]
DIV X [Divides the number in the accumulator by X. Will always round.]
STA X [Stores the value in the accumulator into register X. X cannot be less than 0 or greater than 19.]
RADD X [Adds the value of register X to the accumulator]
RSUB X [Subtracts the value of register X from the accumulator]
RMUL X [Multiplies the value of register X to the accumulator]
RDIV X [Divides the value of register X to the accumulator. Will always round.]
BRP X [Sets the program counter to X if value in accumulator is positive.]
BRPI X [Sets the program counter to X if value in accumulator is positive or 0.]
BRN X [Sets the program counter to X if value in accumulator is negative.]
BRNI X [Sets the program counter to X if value in accumulator is negative or 0.]
BRZ X [Sets the program counter to X if the value in the accumulator is 0.]
BRA X [Sets the program counter to X.]
BRAA [Sets the program counter to the accumulator.]
OUT [Outputs the current value inside of the accumulator to the screen.]
OUTL Y [Outputs the line Y onto the screen.]
DRAA [Outputs the ASCII equivelant of the number in the accumulator.]
OUTN [Goes to next line.]
PAUS [Pauses the program.]
CLR [Clears screen.]
HLT [Stops program.]
*/

static enum OpcodeValues {
	INVALID,
	LDAV,
	LDAR,
	INP,
	ADD,
	SUB,
	MUL,
	DIV,
	RADD,
	RSUB,
	RMUL,
	RDIV,
	STA,
	BRP,
	BRPI,
	BRN,
	BRNI,
	BRZ,
	BRA,
	BRAA,
	OUT,
	OUTL,
	DRAA,
	OUTN,
	PAUS,
	CLR,
	HLT
};

static std::map<std::string, OpcodeValues> mapOpcodeStringValues;

void initialiseMap();

CPU::CPU(RAM *ramReference) {
	this->ramRef = ramReference;
	for (int i = 0; i < 20; i++) {
		this->generalRegisters[i] = 0;
	}
	this->accumulator = 0;
	this->programCounter = 0;
	this->memoryAddressRegister = 0;
	this->memoryDataRegister = "";
	this->currentInstructionRegister = "";

	initialiseMap();
	this->runProgramFromRam();
}

void initialiseMap() {
	mapOpcodeStringValues["LDAV"] = LDAV;
	mapOpcodeStringValues["LDAR"] = LDAR;
	mapOpcodeStringValues["INP"] = INP;
	mapOpcodeStringValues["ADD"] = ADD;
	mapOpcodeStringValues["SUB"] = SUB;
	mapOpcodeStringValues["MUL"] = MUL;
	mapOpcodeStringValues["DIV"] = DIV;
	mapOpcodeStringValues["RADD"] = RADD;
	mapOpcodeStringValues["RSUB"] = RSUB;
	mapOpcodeStringValues["RMUL"] = RMUL;
	mapOpcodeStringValues["RDIV"] = RDIV;
	mapOpcodeStringValues["STA"] = STA;
	mapOpcodeStringValues["BRP"] = BRP;
	mapOpcodeStringValues["BRPI"] = BRPI;
	mapOpcodeStringValues["BRN"] = BRN;
	mapOpcodeStringValues["BRNI"] = BRNI;
	mapOpcodeStringValues["BRZ"] = BRZ;
	mapOpcodeStringValues["BRA"] = BRA;
	mapOpcodeStringValues["BRAA"] = BRAA;
	mapOpcodeStringValues["OUT"] = OUT;
	mapOpcodeStringValues["OUTL"] = OUTL;
	mapOpcodeStringValues["DRAA"] = DRAA;
	mapOpcodeStringValues["OUTN"] = OUTN;
	mapOpcodeStringValues["PAUS"] = PAUS;
	mapOpcodeStringValues["CLR"] = CLR;
	mapOpcodeStringValues["HLT"] = HLT;
}

int CPU::getAccumulator() {
	return this->accumulator;
}

void CPU::loadToAccumulator(int data) {
	this->accumulator = data;
}

int CPU::getRegisterVal(int id) {
	return this->generalRegisters[id];
}
void CPU::loadToRegister(int data, int id) {
	this->generalRegisters[id] = data;
}

/*
Errors:
-Setting program counter to an invalid index.
*/

void checkOperandValidity(std::string operand, int address) {
	if (operand == "") {
		std::cout << "ERROR FOUND AT INDEX " << address << ": INVALID OPERAND - " << operand << "." << std::endl;
		exit(3);
	}
	
	for (int i = 0; i < operand.length(); i++) {
		if (isdigit(operand[i]) == false && operand[i] != '-') {
			std::cout << "ERROR FOUND AT INDEX " << address << ": INVALID OPERAND - " << operand << "." << std::endl;
			exit(3);
		}
	}
}

void checkRegisterValidity(std::string operand, int address) {
	if (std::stoi(operand) < 0 || std::stoi(operand) > 19) {
		std::cout << "ERROR FOUND AT INDEX " << address << ": REGISTER OUT OF RANGE." << std::endl;
	}
}

void CPU::performInstruction(std::string instruction) {
	std::string opcode = instruction.substr(0, instruction.find(' '));
	std::string operand = instruction.substr(instruction.find(' ') + 1, instruction.back());
	int input = 0;
	if (opcode != "INP") {
		std::string operand = instruction.substr(instruction.find(' ') + 1, instruction.back());
	}
	switch (mapOpcodeStringValues[opcode]) {
	case LDAV:
		checkOperandValidity(operand, this->memoryAddressRegister);
		this->accumulator = std::stoi(operand);
		break;
	case LDAR:
		checkOperandValidity(operand, this->memoryAddressRegister);
		checkRegisterValidity(operand, this->memoryAddressRegister);
		this->accumulator = this->generalRegisters[std::stoi(operand)];
		break;
	case INP:
		std::cin >> input;
		if (std::cin.fail()) {
			std::cout << "\nERROR FOUND AT INDEX " << this->memoryAddressRegister << ": INVALID INPUT REGISTERED - " << input << "." << std::endl;
			exit(3);
		}
		this->accumulator = input;
		break;
	case ADD:
		checkOperandValidity(operand, this->memoryAddressRegister);
		this->accumulator += std::stoi(operand);
		break;
	case SUB:
		checkOperandValidity(operand, this->memoryAddressRegister);
		this->accumulator -= std::stoi(operand);
		break;
	case MUL:
		checkOperandValidity(operand, this->memoryAddressRegister);
		this->accumulator *= std::stoi(operand);
		break;
	case DIV:
		checkOperandValidity(operand, this->memoryAddressRegister);
		this->accumulator /= std::stoi(operand);
		break;
	case RADD:
		checkOperandValidity(operand, this->memoryAddressRegister);
		checkRegisterValidity(operand, this->memoryAddressRegister);
		this->accumulator += this->generalRegisters[std::stoi(operand)];
		break;
	case RSUB:
		checkOperandValidity(operand, this->memoryAddressRegister);
		checkRegisterValidity(operand, this->memoryAddressRegister);
		this->accumulator -= this->generalRegisters[std::stoi(operand)];
		break;
	case RMUL:
		checkOperandValidity(operand, this->memoryAddressRegister);
		checkRegisterValidity(operand, this->memoryAddressRegister);
		this->accumulator *= this->generalRegisters[std::stoi(operand)];
		break;
	case RDIV:
		checkOperandValidity(operand, this->memoryAddressRegister);
		checkRegisterValidity(operand, this->memoryAddressRegister);
		this->accumulator /= this->generalRegisters[std::stoi(operand)];
		break;
	case STA:
		checkOperandValidity(operand, this->memoryAddressRegister);
		checkRegisterValidity(operand, this->memoryAddressRegister);
		this->generalRegisters[std::stoi(operand)] = this->accumulator;
		break;
	case BRP:
		if (this->accumulator > 0) {
			checkOperandValidity(operand, this->memoryAddressRegister);
			this->programCounter = std::stoi(operand);
		}
		break;
	case BRPI:
		if (this->accumulator >= 0) {
			checkOperandValidity(operand, this->memoryAddressRegister);
			this->programCounter = std::stoi(operand);
		}
		break;
	case BRN:
		if (this->accumulator < 0) {
			checkOperandValidity(operand, this->memoryAddressRegister);
			this->programCounter = std::stoi(operand);
		}
		break;
	case BRNI:
		if (this->accumulator <= 0) {
			checkOperandValidity(operand, this->memoryAddressRegister);
			this->programCounter = std::stoi(operand);
		}
		break;
	case BRZ:
		if (this->accumulator == 0) {
			checkOperandValidity(operand, this->memoryAddressRegister);
			this->programCounter = std::stoi(operand);
		}
		break;
	case BRA:
		checkOperandValidity(operand, this->memoryAddressRegister);
		this->programCounter = std::stoi(operand);
		break;
	case BRAA:
		this->programCounter = this->accumulator;
		break;
	case OUT:
		std::cout << this->accumulator;
		break;
	case OUTL:
		std::cout << operand;
		break;
	case DRAA:
		std::cout << (char)this->accumulator;
		break;
	case OUTN:
		std::cout << "\n" << std::endl;
		break;
	case PAUS:
		system("pause");
		break;
	case CLR:
		system("cls");
		break;
	case HLT:
		exit(3);
		break;
	default:
		std::cout << "ERROR FOUND AT INDEX " << this->memoryAddressRegister << ": INVALID OPCODE - " << opcode << "." << std::endl;
		this->performInstruction("HLT");
		break;
	}
}

void CPU::runProgramFromRam() {
	while (true) {
		if (this->programCounter < 0 || this->programCounter >(this->ramRef->getInstructionSet().size() - 1)) {
			std::cout << "ERROR: INDEX " << this->programCounter << " OUT OF RANGE." << std::endl;
			this->performInstruction("HLT");
		}

		this->memoryAddressRegister = this->programCounter;
		this->programCounter += 1;
		this->memoryDataRegister = this->ramRef->getInstruction(this->memoryAddressRegister);
		this->currentInstructionRegister = this->memoryDataRegister;
		this->performInstruction(this->currentInstructionRegister);
	}
}