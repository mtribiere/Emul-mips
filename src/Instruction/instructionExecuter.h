#ifndef INSTRUCTION_EXEC_H
#define INSTRUCTION_EXEC_H

#include "memoryManager.h"

void executeInstruction(char *instruction,ProcRegister *registers);
void ADD(int destinationRegister,int operandeRegister1,int operandeRegister2, ProcRegister *registers);

#endif