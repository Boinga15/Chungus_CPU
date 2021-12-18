# Chungus_CPU
A CPU "Emulator" that uses a custom programming language and can run basic programs. It is the first CPU/Emulator I made.

The Chungus CPU runs automatically when the program is run. It uses a seperante RAM file that holds a list of instructions taken from the "program.txt" file in order to run programs. It uses a programming language that is similar to Assembly Language and the language of other CPUs, however it also contains several other functions like multiplication as well as printing lines of text to the screen since I didn't use binary to represent the data.

The CPU has 20 general registers that can be used to temporarly save data. It uses the Von Neumann structure to run. At the moment, it doesn't use any cache however and can only process one command at a time. It's clock speed (or amount of commands it processes per second) was 7310Hz (7.31 KHz) when I checked it on my computer. It may be different however if your computer is stronger/weaker than my.

In order to program the Chungus CPU, use the "program.txt" file. Write your commands in there and then run the program. Here are the different commands you can put into the file. X represents any whole number while Y represents any string data (e.g. "Testing strings" without the quotation marks):

LDAV X [Loads the value X into the accumulator.]

LDAR X [Loads the value of register X into the accumulator.]

INP [Recieves input from the user and stores the result in the accumulator.]

ADD X [Adds X to the accumulator.]

SUB X [Subtracts X from the accumulator.]

MUL X [Multiplies the number in the accumulator by X.]

DIV X [Divides the number in the accumulator by X. Will always round the resultant value.]

STA X [Stores the value inside of the accumulator into register X.]

RADD X [Adds the value of register X to the accumulator.]

RSUB X [Subtracts the value of register X from the accumulator.]

RMUL X [Multiplies the the number in the accumulator by the number in register X.]

RDIV X [Divides the value of register X to the accumulator. Will always round.]

BRP X [Sends the program to the command at index X if the number in the accumulator is positive (not 0).]

BRPI X [Sends the program to the command at index X if the number in the accumulator is positive or zero.]

BRN X [Sends the program to the command at index X if the number in the accumulator is negative (not 0).]

BRNI X [Sends the program to the command at index X if the number in the accumulator is negative or zero.]

BRZ X [Sends the program to the command at index X if the number in the accumulator is zero.]

BRA X [Sends the program to the command at index X no matter what.]

BRAA [Sends the program to the command at index Z, where Z represents the number inside of the accumulator.]

OUT [Outputs the current value inside of the accumulator.]

OUTL Y [Outputs the line Y.]

OUTN [Goes to the next line.]

DRAA [Outputs the ASCII equivelant of the number inside of the accumulator.]

PAUS [Pauses the program until the user presses enter.]

CLR [Clears the screen.]

HLT [Stops the program.]
