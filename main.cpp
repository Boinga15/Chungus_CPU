/*
Implement:
-CPU to handle instruction processing.
-GPU to handle outputting things to the screen.
-RAM to hold instruction list (+instruction set).
-ROM to hold boot-up instructions.
*/

#include<iostream>
#include "cpu.h"
#include "ram.h"

int main() {
	RAM ramInst = RAM();
	CPU cpuInst = CPU(&ramInst);
}