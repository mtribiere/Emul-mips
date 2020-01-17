#ifndef MIPS_INSTRUCTIONS_H
#define MIPS_INSTRUCTIONS_H

/* Dans ce fichier, nous assumons que les opérandes sont des chaines de 5 bits */

void ADD(long int *oper1, long int *oper2, long int *result);

void SUB(long int *oper1, long int *oper2, long int *result);

void AND(long int *oper1, long int *oper2, long int *result);

void OR(long int *oper1, long int *oper2, long int *result);

void XOR(long int *oper1, long int *oper2, long int *result);

void MULT(long int *oper1, long int *oper2, long int *resultHigh, long int *resultLow);

void DIV(long int *oper1, long int *oper2, long int *result);

void BEQ(long int *oper1, long int *oper2, long int *result);

void BGTZ(long int *oper1, long int *result);

void BLEZ(long int *oper1, long int *result);

void BNE(long int *oper1, long int *oper2, long int *result);

void ROTR(long int *oper1, int index_rotation, long int *result);

void SRL(long int *oper1, int index_rotation, long int *result);

void SLL(long int *oper1, int index_rotation, long int *result);

void SLT(long int *oper1, long int *oper2, long int *result);

void LUI(long int *oper1, long int *result);

long int *arithmetic(long int *oper1, long int *oper2, char *instruction);

#endif