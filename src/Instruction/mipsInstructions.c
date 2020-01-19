#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "memoryManager.h"
#include "Instruction/mipsInstructions.h"
/* Dans ce fichier, nous assumons que les opérandes sont déjà convertis en entiers décimaux */

void ADD(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)
{
    /* Charger les deux opérandes */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);
    long int oper2 = loadFromRegister(operandeRegister2,*registers);

    /* Faire l'addition */
    long int result = oper1 + oper2;

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}

void ADDI(int destinationRegister, int operandeRegister1, int operande2, ProcRegister *registers)
{
    /* Charger les deux opérandes */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);

    /* Faire l'addition immédiate */
    /* TRAITER LE CAS Où LE COMPLEMENT A 2 CRéE UNE INTEGER OVERFLOW EXCEPTION */
    long int result = oper1 + operande2;

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}

void SUB(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)
{
    /* Charger les deux opérandes */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);
    long int oper2 = loadFromRegister(operandeRegister2,*registers);

    /* Faire la soustraction */
    long int result = oper1 - oper2;

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}

void AND(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)
{
    /* Charger les deux opérandes */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);
    long int oper2 = loadFromRegister(operandeRegister2,*registers);

    /* Faire l'opération ET bit à bit */
    long int result = oper1 & oper2;

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}

void OR(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)
{
    /* Charger les deux opérandes */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);
    long int oper2 = loadFromRegister(operandeRegister2,*registers);

    /* Faire l'opération OU bit à bit */
    long int result = oper1 | oper2;

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}

void XOR(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)
{
    /* Charger les deux opérandes */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);
    long int oper2 = loadFromRegister(operandeRegister2,*registers);

    /* Faire l'opération OU exclusif */
    long int result = oper1 ^ oper2;

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}

