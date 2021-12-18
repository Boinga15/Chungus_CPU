#include<iostream>
#include "cpu.h"
#include "ram.h"

int main() {
	RAM ramInst = RAM();
	CPU cpuInst = CPU(&ramInst);
}
