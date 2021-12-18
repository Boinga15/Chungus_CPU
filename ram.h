#pragma once
#define RAM_H
#ifdef RAM_H

#include<string>
#include<vector>

class RAM {
private:
	std::vector<std::string> instructionSet;
public:
	RAM();
	void loadInstructionSetFromFile(std::string fileName);
	std::string getInstruction(int id);
	std::vector<std::string> getInstructionSet();
};

#endif RAM_H