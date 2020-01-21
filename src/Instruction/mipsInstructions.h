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

/*long int *arithmetic(long int *oper1, long int *oper2, char *instruction);*/

#endif