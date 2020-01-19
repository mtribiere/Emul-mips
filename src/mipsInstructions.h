#ifndef MIPS_INSTRUCTIONS_H
#define MIPS_INSTRUCTIONS_H

/* Dans ce fichier, nous assumons que les opérandes sont des chaines de 5 bits */

void ADD(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers);

void ADDI(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers);

void SUB(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers);

void AND(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers);

void OR(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers);

void XOR(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers);

void MULT(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers);

void DIV(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers);

void BEQ(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers);

void BGTZ(int destinationRegister, int operandeRegister1, ProcRegister *registers);

void BLEZ(int destinationRegister, int operandeRegister1, ProcRegister *registers);

void BNE(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)

void ROTR(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)

void SRL(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)

void SLL(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)

void SLT(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)

void LUI(int destinationRegister, int operandeRegister1, ProcRegister *registers)

/*long int *arithmetic(long int *oper1, long int *oper2, char *instruction);*/

#endif