#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Instruction/instructionInfo.h"

int getInstructionType(const char *s){

	int toReturnType=-1;

	//Copier l'instruction
	char instruction[MAX_INSTRUCTION_LENGTH] = {0};
	int index = 0;
	while(s[index] != ' '){
		instruction[index] = s[index];
		index++;
	}

	//Declaration du tableau des types R
	char *typeRInstruction[]={
		"ADD",
		"SUB",
		"AND",	
		"OR",
	};

	//Declaration du tableau des types I
	char *typeIInstruction[]={
		"ADDI",
		"BEQ",
		"BNE",
		"BGTZ",
		"BLEZ",
		"LW",
		"SW"
	};

	//Declaration du tableau des types J
	char *typeJInstruction[]={
	
	};


	//Verifier dans tous les tableaux l'instruction
	for(int i = 0;i<sizeof(typeRInstruction)/sizeof(char*);i++)
		if(strcmp(instruction,typeRInstruction[i]) == 0)
			toReturnType = 0;
	
	for(int i = 0;i<sizeof(typeIInstruction)/sizeof(char*) && toReturnType == -1;i++)
		if(strcmp(instruction,typeIInstruction[i]) == 0)
			toReturnType = 1;

	for(int i = 0;i<sizeof(typeJInstruction)/sizeof(char*) && toReturnType == -1;i++)
		if(strcmp(instruction,typeJInstruction[i]) == 0)
			toReturnType = 2;
	
	//Stopper si l'instruction n'est pas connue
	if(toReturnType == -1){
		printf("L'instruction %s n'est pas connue - Arret\n",instruction);
		exit(50);
	}

	return toReturnType;
}

int getIsSpecial(const char *s){
	
	int isSpecial = 0;

	//Declaration du tableau des spécials
	char *specialInstructions[] = {
		"ADD",
		"SUB",
		"AND",
		"OR"
	};

	//Copier l'instruction
	char instruction[MAX_INSTRUCTION_LENGTH] = {0};
	int index = 0;
	while(s[index] != ' '){
		instruction[index] = s[index];
		index++;
	}

	for(int i = 0;i < sizeof(specialInstructions)/sizeof(char*);i++){

		if(strcmp(instruction,specialInstructions[i]) == 0){
			isSpecial = 1;
		}

	}

	return isSpecial;
}


/* Prend en paramètres une instruction TERMINEE PAR UN ' ' ex. "ADDI " */
/* Charge l'opcode de cette instruction ex. 001000 dans le tableau opcode */
void getOperationCode(char *instruction, char *opcode)
{
	int index=0;
	int size=0;

	char *instruction_tmp;

	/* Calcule de la taille à allouer */

	while(instruction[size]!=' ')
	{
		size++;	
	}
	instruction_tmp=malloc(size*sizeof(char));

	for(index=0; index < size; index++) instruction_tmp[index]=instruction[index];
	instruction_tmp[size]='\0';
	for(index=0;index<6;index++) opcode[index]=0;

	//printf("\n\n%d %s %d %d %d\n\n",size, instruction_tmp,strcmp(instruction,"AND\0"),strcmp("AND\0","AND\0"),memcmp(instruction_tmp,"AND\0",size));

	if(memcmp(instruction_tmp,"ADD",size)==0) strcpy(opcode,"100000");
	else if(memcmp(instruction,"ADDI",size)==0) strcpy(opcode,"001000");
	else if(memcmp(instruction,"AND",size)==0) strcpy(opcode,"100100");

	else if(memcmp(instruction,"BEQ",size)==0) strcpy(opcode,"000100");
	else if(memcmp(instruction,"BNE",size)==0) strcpy(opcode,"000101");
	else if(memcmp(instruction,"BLEZ",size)==0) strcpy(opcode,"000110");
	else if(memcmp(instruction,"BGTZ",size)==0) strcpy(opcode,"000111");


	else if(memcmp(instruction,"DIV",size)==0) strcpy(opcode,"011010");
	else if(memcmp(instruction,"J",size)==0) strcpy(opcode,"000010");
	else if(memcmp(instruction,"JAL",size)==0) strcpy(opcode,"000011");
	else if(memcmp(instruction,"JR",size)==0) strcpy(opcode,"001000");

	else if(memcmp(instruction,"LUI",size)==0) strcpy(opcode,"001111");
	else if(memcmp(instruction,"LW",size)==0) strcpy(opcode,"100011");

	else if(memcmp(instruction,"MFHI",size)==0) strcpy(opcode,"010000");
	else if(memcmp(instruction,"MFLO",size)==0) strcpy(opcode,"010010");
	else if(memcmp(instruction,"MULT",size)==0) strcpy(opcode,"011000");

	else if(memcmp(instruction,"NOP",size)==0) strcpy(opcode,"000000");
	else if(memcmp(instruction,"OR",size)==0) strcpy(opcode,"100101");
	else if(memcmp(instruction,"ROTR",size)==0) strcpy(opcode,"000010");

	else if(memcmp(instruction,"SLL",size)==0) strcpy(opcode,"000000");
	else if(memcmp(instruction,"SLT",size)==0) strcpy(opcode,"101010");
	else if(memcmp(instruction,"SRL",size)==0) strcpy(opcode,"000010");
	else if(memcmp(instruction,"SUB",size)==0) strcpy(opcode,"100010");
	
	else if(memcmp(instruction,"SW",size)==0) strcpy(opcode,"101011");
	else if(memcmp(instruction,"SYSCALL",size)==0) strcpy(opcode,"001100");
	else if(memcmp(instruction,"XOR",size)==0) strcpy(opcode,"100110");

	//Liberer la memoire
	//8==>
	free(instruction_tmp);
}