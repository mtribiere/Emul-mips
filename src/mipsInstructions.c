#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mipsInstructions.h"
#include "memoryManager.h"
#include "utils.h"

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

void ADDI(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)
{
    /* Charger les deux opérandes */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);

    /* Faire l'addition immédiate */
    /* TRAITER LE CAS Où LE COMPLEMENT A 2 CRéE UNE INTEGER OVERFLOW EXCEPTION */
    long int result = oper1 + operandeRegister2;

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
    */* Charger les deux opérandes */
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

void DIV(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)
{
    /* Charger les deux opérandes */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);
    long int oper2 = loadFromRegister(operandeRegister2,*registers);

    /* Faire la division */
    long int result = (long int) oper1 / oper2;

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}

/* A REPRENDRE */
void MULT(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)
{
    /* Charger les deux opérandes */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);
    long int oper2 = loadFromRegister(operandeRegister2,*registers);

    /* Faire la multiplication */
    long int resultLow;
    long int resultHigh;

    /* Si le résultat excède ou égale 2^32, le résultat sera converti en un nombre négatif */
    /* Nous traitons donc le cas en avance pour conserver un long int signé */
    if (oper1 >= myPow(2,16) || (oper2 >= myPow(2,16))) 
    /* Pas du tout la seule combinaison possible pour égaler ou dépasser 2^32 !! */
    /* Faire plutôt un if (log2(oper1) + log2(oper2) >= 32) */
    {
        printf("\n Pour l'instant tailles opérandes trop grande \n");
    }
    else resultLow = oper1 * oper2;

    /* Stocker le résultat */
    storeInRegister(resultLow, destinationRegister, registers);
}

void BEQ(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)
{
    /* Charger les deux opérandes */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);
    long int oper2 = loadFromRegister(operandeRegister2,*registers);

    /* Faire la comparaison */
    long int result;
    if (oper1==oper2) result=1;
    else result=0;

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}

void BGTZ(int destinationRegister, int operandeRegister1, ProcRegister *registers)
{
    /* Charger l'opérande */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);

    /* Faire la comparaison */
    long int result;
    if (oper1 > 0) result=1;
    else result=0;

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}

void BLEZ(int destinationRegister, int operandeRegister1, ProcRegister *registers)
{
    /* Charger l'opérande */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);

    /* Faire la comparaison */
    long int result;
    if (oper1 <= 0) result=1;
    else result=0;

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}

void BNE(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)
{
    /* Charger les deux opérandes */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);
    long int oper2 = loadFromRegister(operandeRegister2,*registers);

    /* Faire la comparaison */
    long int result;
    if (oper1 != oper2) result=1;
    else result=0;

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}

void ROTR(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)
{
    /* Charger l'opérande */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);
    int index_rotation = operandeRegister2 % 32;

    /* Faire la rotation */
    long int result;
    int index_oper1;
    int index_result;

    if(index_rotation < 0) index_rotation = 32+index_rotation;

    int *result_tmp=malloc(32*sizeof(int));
    int *oper1_tmp=intToBin(oper1);

    printf("\n Index rotation : %d \n\n",index_rotation);

    for(index_oper1=31; index_oper1 >= 0; index_oper1--)
    {
        index_result=index_oper1 + index_rotation;
        if(index_oper1 + index_rotation >= 32) index_result-=32;

        *(result_tmp+index_result) = *(oper1_tmp+index_oper1);
    }

    for(index_result=0; index_result < 32; index_result++)
    {
        printf("%d",*(result_tmp+index_result));
    }

    result=binToInt(result_tmp);
    free(result_tmp);

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}

void SRL(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)
{
    /* Charger l'opérande */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);
    int index_rotation = operandeRegister2 % 32;

    /* Faire le décalage vers la droite */
    long int result = oper1 >> index_rotation;

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}

void SLL(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)
{
    /* Charger l'opérande */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);
    int index_rotation = operandeRegister2 % 32;

    /* Faire le décalage vers la gauche */
    long int result = oper1 << index_rotation;

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}

void SLT(int destinationRegister, int operandeRegister1, int operandeRegister2, ProcRegister *registers)
{
    /* Charger les deux opérandes */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);
    long int oper2 = loadFromRegister(operandeRegister2,*registers);

    /* Faire la comparaison */
    long int result;
    if(oper1 < oper2) result=1;
    else result=0;

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}

void LUI(int destinationRegister, int operandeRegister1, ProcRegister *registers)
{
    /* Charger l'opérande */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);

    /* Faire l'addition */
    long int result=0;
    int *oper1_tmp = intToBin(oper1);
    int index;

    for (index=31; index >= 16; index--)
    {
        result = result + myPow(2,16)*myPow(2,31-index)*oper1_tmp[index];
    }

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}
/*
long int *arithmetic(long int *oper1, long int *oper2, char *instruction)
{
    
    long int *result;
    result=malloc(sizeof(long int));
    long int *result_low;
    result_low=malloc(sizeof(long int));
    */

    /* Nous assumons de faire la même chose pour ADD et ADDI */
    /* car les éventuelles transformations en entiers décimaux ont déjà été faites */
/*    if(memcmp(instruction,"ADD",3)==0) ADD(oper1,oper2,result);

    else if(memcmp(instruction,"SUB",3)==0) SUB(oper1,oper2,result);

    else if(memcmp(instruction,"AND",3)==0) AND(oper1,oper2,result);

    else if(memcmp(instruction,"OR",2)==0) OR(oper1,oper2,result);

    else if(memcmp(instruction,"XOR",3)==0) XOR(oper1,oper2,result);

    else if(memcmp(instruction,"DIV",3)==0) DIV(oper1,oper2,result);

    else if(memcmp(instruction,"MULT",4)==0)
    {
        MULT(oper1,oper2,result,result_low);
*/      /* MULT fait deux return de long int de 32 bits dans deux registres spéciaux */
        /* Il faudra donc écrire directement ici dans les registres spéciaux concernés */
    }

/*    else if(memcmp(instruction,"BEQ",3)==0) BEQ(oper1,oper2,result);

    else if(memcmp(instruction,"BGTZ",4)==0) BGTZ(oper1,result);

    else if(memcmp(instruction,"BLEZ",4)==0) BLEZ(oper1,result);

    else if(memcmp(instruction,"BNE",3)==0) BNE(oper1,oper2,result);

    else if(memcmp(instruction,"ROTR",4)==0) ROTR(oper1,(int) (*oper2),result);

    else if(memcmp(instruction,"SRL",3)==0) SRL(oper1,(int) (*oper2),result);

    else if(memcmp(instruction,"SLL",3)==0) SLL(oper1,(int) (*oper2),result);

    else if(memcmp(instruction,"SLT",3)==0) SLT(oper1,oper2,result);

    else if(memcmp(instruction,"LUI",3)==0) LUI(oper1,result);

    return result;
}
*/
