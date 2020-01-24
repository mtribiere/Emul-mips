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

void BEQ(int operandeRegister1,int operandeRegister2,char *labelToJump,ProcRegister *registers,char *labelTable[]){

	//Comparer les deux registres
	if(loadFromRegister(operandeRegister1,*registers) == loadFromRegister(operandeRegister2,*registers)){
		//Trouver la ligne où sauter
		int toJump = getLineFromLabel(labelToJump,labelTable);

		//Effectuer le saut
		storeInRegister(toJump-1,PC_REGISTER,registers);

	}

}


void BNE(int operandeRegister1,int operandeRegister2,char *labelToJump,ProcRegister *registers,char *labelTable[]){

	//Comparer les deux registres
	if(loadFromRegister(operandeRegister1,*registers) != loadFromRegister(operandeRegister2,*registers)){
		//printf("JUMP !!\n");
		//Trouver la ligne où sauter
		int toJump = getLineFromLabel(labelToJump,labelTable);

		//Effectuer le saut
		storeInRegister(toJump-1,PC_REGISTER,registers);

	}

}

void LW(int destinationRegister, int baseRegister,int offset, ProcRegister *registers,MainMemory mainMemory){

	//Charger la valeur
	int toStore = loadFromMemory(loadFromRegister(baseRegister,*registers),mainMemory);

	//Stocker la valeur
	storeInRegister(toStore,destinationRegister,registers);

}

void SW(int baseRegister,int offset ,int sourceRegister ,ProcRegister registers,MainMemory *mainMemory){

	//Recuperer la donnée
	long int toStore = loadFromRegister(sourceRegister,registers);

	//Recuperer l'adresse de destination
	long int destinationAdress = loadFromRegister(baseRegister,registers);

	//Stocker la donnée
	storeInMemory(toStore,(destinationAdress+offset),mainMemory);

}

void ROTR(int destinationRegister, int operandeRegister1, int operande2, ProcRegister *registers)
{
    /* Charger l'opérande */

    long int operande1 = loadFromRegister(operandeRegister1,*registers);
    int index_rotation = operande2 % 32;

    /* Faire la rotation */

    long int result;
    int index_oper1;
    int index_result;

    if(index_rotation < 0) index_rotation = 32+index_rotation;

    int *result_tmp=malloc(32*sizeof(int));
    int *oper1_tmp=malloc(32*sizeof(int));

    convertLongIntToBin(operande1, oper1_tmp);

    for(index_oper1=31; index_oper1 >= 0; index_oper1--)
    {
        index_result=index_oper1 + index_rotation;
        if(index_oper1 + index_rotation >= 32) index_result-=32;

        *(result_tmp+index_result) = *(oper1_tmp+index_oper1);
    }

    result=convertBinToLongInt(result_tmp);

    free(result_tmp);
    free(oper1_tmp);

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);

}


void SRL(int destinationRegister, int operandeRegister1, int operande2, ProcRegister *registers)
{
    /* Charger l'opérande */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);
    int index_rotation = operande2 % 32;

    /* Faire le décalage vers la droite */
    long int result = oper1 >> index_rotation;

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);
}

void SLL(int destinationRegister, int operandeRegister1, int operande2, ProcRegister *registers)
{
    /* Charger l'opérande */
    long int oper1 = loadFromRegister(operandeRegister1,*registers);
    int index_rotation = operande2 % 32;

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

    long int operande1 = loadFromRegister(operandeRegister1,*registers);

    /* Faire l'addition */

    long int result=0;
    int *oper1_tmp=malloc(32*sizeof(int));
    int index;

    /* operande1, oper1_tmp */
    convertLongIntToBin(operande1, oper1_tmp);

    for (index=31; index >= 16; index--)
    {
        result = result + myPow(2,16)*myPow(2,31-index)*oper1_tmp[index];
    }

    /* Pour le test : */
    convertLongIntToBin(result, oper1_tmp);

    free(oper1_tmp);

    /* Stocker le résultat */
    storeInRegister(result, destinationRegister, registers);

}

void RIP(int baseRegister, int offset, int sourceRegister, ProcRegister registers,MainMemory mainMemory){

	FILE *fptr; 
  
    char filename[100] = "src/Instruction/yard"; 
	char c;

	
    fptr = fopen(filename, "r"); 
    if (fptr == NULL) 
    { 
		printf("Et c'est dans la boite ! \n");
		exit(99); 
    } 
  
    c = fgetc(fptr); 
    while (c != EOF) 
    { 
        printf ("%c", c); 
        c = fgetc(fptr); 
    } 
  
    fclose(fptr); 

	exit(99);

}