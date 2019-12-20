#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mipsInstructions.h"
#include "utils.h"

/* Dans ce fichier, nous assumons que les opérandes sont des chaines de 5 bits */

int myPow(int x, int y)
{
    int result=1;

    while(y > 0)
    {
        result*=x;
        y--;
    }

    return result;
}

void ADD(int *oper1, int *oper2, int *result)
{
    int index;
    int carry=0;

    for (index=0; index < 5; index++)
    {
        result[index]=oper1[index]+oper2[index]+carry;
        carry=0;
        if(result[index]>=2)
        {
            result[index]-=2;
            carry=1;
        }
    }
}

void AND(int *oper1, int *oper2, int *result)
{
    int index;
    for(index=0; index < 5; index++) result[index]=(oper1[index]) & (oper2[index]);
}

void OR(int *oper1, int *oper2, int *result)
{
    int index;
    for (index=0; index < 5; index++) result[index]=(oper1[index]) | (oper2[index]);
}

void DIV(int *oper1, int *oper2, int *result)
{
    int number_1 = oper1[0]+2*oper1[1]+4*oper1[2]+8*oper1[3]+16*oper1[4];
    int number_2 = oper2[0]+2*oper2[1]+4*oper2[2]+8*oper2[3]+16*oper2[4];

    int result_div = (int) number_1/number_2;
    /* It is said it is assumed if the program crashes due to division by 0, so ... */

    int index;

    for(index=0; index < 5; index++)
    {
        if(result_div >= myPow(2,index))
        {
            result[index]=1;
            result_div-=myPow(2,index);
        }
        else result[index]=0;
    }
}

void MULT(int *oper1, int *oper2, int *result)
{
    int number_1 = oper1[0]+2*oper1[1]+4*oper1[2]+8*oper1[3]+16*oper1[4];
    int number_2 = oper2[0]+2*oper2[1]+4*oper2[2]+8*oper2[3]+16*oper2[4];

    int result_mult = (int) number_1*number_2;

    int index;

    for(index=0; index < 5; index++)
    {
        if(result_mult >= myPow(2,index))
        {
            result[index]=1;
            result_mult-=myPow(2,index);
        }
        else result[index]=0;
    }
}

void BEQ(int *oper1, int *oper2, int *result)
{
    int number_1 = oper1[0]+2*oper1[1]+4*oper1[2]+8*oper1[3]+16*oper1[4];
    int number_2 = oper2[0]+2*oper2[1]+4*oper2[2]+8*oper2[3]+16*oper2[4];

    if (number_1==number_2) result[0]=1;
    else
    {
        result[0]=0;
        result[1]=0;
        result[2]=0;
        result[3]=0;
        result[4]=0;
    }
}

void BGTZ(int *oper1, int *result)
{
    int number_1 = oper1[0]+2*oper1[1]+4*oper1[2]+8*oper1[3]+16*oper1[4];

    if (number_1 > 0) result[0]=1;
    else
    {
        result[0]=0;
        result[1]=0;
        result[2]=0;
        result[3]=0;
        result[4]=0;
    }
}

void BLEZ(int *oper1, int *result)
{
    int number_1 = oper1[0]+2*oper1[1]+4*oper1[2]+8*oper1[3]+16*oper1[4];

    if (number_1 <= 0) result[0]=1;
    else
    {
        result[0]=0;
        result[1]=0;
        result[2]=0;
        result[3]=0;
        result[4]=0;
    }
}

void BNE(int *oper1, int *oper2, int *result)
{
    int number_1 = oper1[0]+2*oper1[1]+4*oper1[2]+8*oper1[3]+16*oper1[4];
    int number_2 = oper2[0]+2*oper2[1]+4*oper2[2]+8*oper2[3]+16*oper2[4];

    if(number_1 != number_2) result[0]=1;
    else
    {
        result[0]=0;
        result[1]=0;
        result[2]=0;
        result[3]=0;
        result[4]=0;
    }
}

void ROTR(int *oper1, int index_rotation, int *result)
{
    int index;

    for(index=0; index < 5; index++)
    {
        if(index+index_rotation < 0) result[index]=oper1[index+index_rotation+5];
        else if(index+index_rotation >= 5) result[index]=oper1[index+index_rotation-5];
        else result[index]=oper1[index+index_rotation];
    }
}

void SRL(int *oper1, int index_rotation, int *result)
{
    int number_1 = oper1[0]+2*oper1[1]+4*oper1[2]+8*oper1[3]+16*oper1[4];

    int result_srl = number_1 >> index_rotation;

    int index;

    for(index=0; index < 5; index++)
    {
        if(result_srl >= myPow(2,index))
        {
            result[index]=1;
            result_srl-=myPow(2,index);
        }
        else result[index]=0;
    }
}

void SLL(int *oper1, int index_rotation, int *result)
{
    int number_1 = oper1[0]+2*oper1[1]+4*oper1[2]+8*oper1[3]+16*oper1[4];

    int result_sll = number_1 << index_rotation;

    int index;

    for(index=0; index < 5; index++)
    {
        if(result_sll >= myPow(2,index))
        {
            result[index]=1;
            result_sll-=myPow(2,index);
        }
        else result[index]=0;
    }
}

int *arithmetic(int *oper1, int *oper2, char *instruction)
{
    int index_rotation_or_shift=-3;

    int *result;
    result=malloc(6*sizeof(int));

    /* Si oper1 et oper2 ne sont pas des int* mais des char* : les convertir en int* ici */
    if(memcmp(instruction,"ADD",3)==0) ADD(oper1,oper2,result);

    else if(memcmp(instruction,"AND",3)==0) AND(oper1,oper2,result);

    else if(memcmp(instruction,"OR",2)==0) OR(oper1,oper2,result);

    else if(memcmp(instruction,"DIV",3)==0) DIV(oper1,oper2,result);

    else if(memcmp(instruction,"MULT",4)==0) MULT(oper1,oper2,result);
    
    else if(memcmp(instruction,"BEQ",3)==0) BEQ(oper1,oper2,result);

    else if(memcmp(instruction,"BGTZ",4)==0) BGTZ(oper1,result);

    else if(memcmp(instruction,"BLEZ",4)==0) BLEZ(oper1,result);

    else if(memcmp(instruction,"BNE",3)==0) BNE(oper1,oper2,result);

    else if(memcmp(instruction,"ROTR",4)==0) ROTR(oper1,index_rotation_or_shift,result);

    else if(memcmp(instruction,"SRL",3)==0) SRL(oper1,index_rotation_or_shift,result);

    else if(memcmp(instruction,"SLL",3)==0) SLL(oper1,index_rotation_or_shift,result);

    return result;
}
