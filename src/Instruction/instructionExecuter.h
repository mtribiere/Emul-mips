#ifndef INSTRUCTION_EXEC_H
#define INSTRUCTION_EXEC_H

#include "memoryManager.h"

void executeInstruction(char *instruction,ProcRegister *registers,MainMemory *mainMemory,char *labelTable[]);

#endif