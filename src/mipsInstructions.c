#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mipsInstructions.h"
#include "utils.h"

/* Dans ce fichier, nous assumons que les opérandes sont déjà convertis en entiers décimaux */

void ADD(long int *oper1, long int *oper2, long int *result)
{
    *result=(*oper1) + (*oper2);
}

void SUB(long int *oper1, long int *oper2, long int *result)
{
    *result=(*oper1) - (*oper2);
}

void AND(long int *oper1, long int *oper2, long int *result)
{
    *result = (*oper1) & (*oper2);
}

void OR(long int *oper1, long int *oper2, long int *result)
{
    *result = (*oper1) | (*oper2);
}

void XOR(long int *oper1, long int *oper2, long int *result)
{
    *result = (*oper1) ^ (*oper2);
}

void DIV(long int *oper1, long int *oper2, long int *result)
{
    *result = (long int) (*oper1)/(*oper2);
}

void MULT(long int *oper1, long int *oper2, long int *resultHigh, long int *resultLow)
{
    /* Si le résultat excède ou égale 2^32, le résultat sera converti en un nombre négatif */
    /* Nous traitons donc le cas en avance pour conserver un long int signé */
    if (*oper1 >= myPow(2,16) && (*oper2 >= myPow(2,16)))
    {
        printf("\n Pour l'instant tailles opérandes trop grande \n");
    }
    else *resultHigh = (*oper1)*(*oper2);
}

void BEQ(long int *oper1, long int *oper2, long int *result)
{
    if ((*oper1)==(*oper2)) *result=1;
    else *result=0;
}

void BGTZ(long int *oper1, long int *result)
{
    if ((*oper1) > 0) *result=1;
    else *result=0;
}

void BLEZ(long int *oper1, long int *result)
{
    if ((*oper1) <= 0) *result=1;
    else *result=0;
}

void BNE(long int *oper1, long int *oper2, long int *result)
{
    if((*oper1) != (*oper2)) *result=1;
    else *result=0;
}

void ROTR(long int *oper1, int index_rotation, long int *result)
{
    int index_oper1;
    int index_result;

    if(index_rotation < 0) index_rotation = 32+index_rotation;

    int *result_tmp=malloc(32*sizeof(int));
    int *oper1_tmp=intToBin(*oper1);

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

    *result=binToInt(result_tmp);
    free(result_tmp);
}

void SRL(long int *oper1, int index_rotation, long int *result)
{
    *result = (*oper1) >> index_rotation;
}

void SLL(long int *oper1, int index_rotation, long int *result)
{
    *result = (*oper1) << index_rotation;
}

void SLT(long int *oper1, long int *oper2, long int *result)
{
    if(*oper1 < *oper2) *result=1;
    else *result=0;
}

void LUI(long int *oper1, long int *result)
{
    int *oper1_tmp = intToBin(*oper1);
    int index;

    *result=0;
    for (index=31; index >= 16; index--)
    {
        *result+=myPow(2,16)*myPow(2,31-index)*oper1_tmp[index];
    }
}

long int *arithmetic(long int *oper1, long int *oper2, char *instruction)
{
    long int *result;
    result=malloc(sizeof(long int));
    long int *result_low;
    result_low=malloc(sizeof(long int));

    /* Nous assumons de faire la même chose pour ADD et ADDI */
    /* car les éventuelles transformations en entiers décimaux ont déjà été faites */
    if(memcmp(instruction,"ADD",3)==0) ADD(oper1,oper2,result);

    else if(memcmp(instruction,"SUB",3)==0) SUB(oper1,oper2,result);

    else if(memcmp(instruction,"AND",3)==0) AND(oper1,oper2,result);

    else if(memcmp(instruction,"OR",2)==0) OR(oper1,oper2,result);

    else if(memcmp(instruction,"XOR",3)==0) XOR(oper1,oper2,result);

    else if(memcmp(instruction,"DIV",3)==0) DIV(oper1,oper2,result);

    else if(memcmp(instruction,"MULT",4)==0)
    {
        MULT(oper1,oper2,result,result_low);
        /* MULT fait deux return de long int de 32 bits dans deux registres spéciaux */
        /* Il faudra donc écrire directement ici dans les registres spéciaux concernés */
    }

    else if(memcmp(instruction,"BEQ",3)==0) BEQ(oper1,oper2,result);

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
