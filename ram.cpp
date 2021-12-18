#include "ram.h"
#include<iostream>
#include <string>
#include <vector>
#include<fstream>
#include<limits>

RAM::RAM() {
	this->instructionSet = {};
	this->loadInstructionSetFromFile("program.txt");
}

std::fstream& getLine(std::fstream& file, unsigned int num) {
	file.seekg(std::ios::beg);
	for (int i = 0; i < num - 1; ++i) {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return file;
}

void RAM::loadInstructionSetFromFile(std::string fileName) {
	std::fstream file(fileName);
	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			this->instructionSet.push_back(line);
		}
	}
}

std::string RAM::getInstruction(int id) {
	return this->instructionSet[id];
}

std::vector<std::string> RAM::getInstructionSet() {
	return this->instructionSet;
}