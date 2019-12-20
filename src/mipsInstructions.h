#ifndef MIPS_INSTRUCTIONS_H
#define MIPS_INSTRUCTIONS_H

/* Dans ce fichier, nous assumons que les opérandes sont des chaines de 5 bits */

void ADD(int *oper1, int *oper2, int *result);

void AND(int *oper1, int *oper2, int *result);

void OR(int *oper1, int *oper2, int *result);

void MULT(int *oper1, int *oper2, int *result);

void DIV(int *oper1, int *oper2, int *result);

void BEQ(int *oper1, int *oper2, int *result);

void BGTZ(int *oper1, int *result);

void BLEZ(int *oper1, int *result);

void BNE(int *oper1, int *oper2, int *result);

void ROTR(int *oper1, int index_rotation, int *result);

void SRL(int *oper1, int index_rotation, int *result);

void SLL(int *oper1, int index_rotation, int *result);

int *arithmetic(int *oper1, int *oper2, char *instruction);

#endif