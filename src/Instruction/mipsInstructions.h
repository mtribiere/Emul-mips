#ifndef MIPS_INSTRUCTIONS_H
#define MIPS_INSTRUCTIONS_H

/* Dans ce fichier, nous assumons que les opérandes sont des chaines de 5 bits */

void ADD(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers);

void ADDI(int destinationRegister, int operandeRegister1, int operande2, ProcRegister *registers);

void SUB(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers);

void AND(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers);

void OR(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers);

void XOR(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers);

void BEQ(int operandeRegister1,int operandeRegister2,char *labelToJump,ProcRegister *registers,char *labelTable[]);

void BNE(int operandeRegister1,int operandeRegister2,char *labelToJump,ProcRegister *registers,char *labelTable[]);

void LW(int destinationRegister, int baseRegister,int offset, ProcRegister *registers,MainMemory mainMemory);

void SW(int baseRegister,int offset ,int sourceRegister ,ProcRegister registers,MainMemory *mainMemory);

void RIP(int baseRegister, int offset, int sourceRegister, ProcRegister registers,MainMemory mainMemory);

void ROTR(int destinationRegister, int operandeRegister1, int operande2, ProcRegister *registers);

void SRL(int destinationRegister, int operandeRegister1, int operande2, ProcRegister *registers);

void SLL(int destinationRegister, int operandeRegister1, int operande2, ProcRegister *registers);

void SLT(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers);

void LUI(int destinationRegister, int operandeRegister1, ProcRegister *registers);

#endif