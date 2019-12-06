#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Instruction/instructionInfo.h"

int getInstructionType(const char *s){

	int toReturnType=-1;

	//Copier l'instruction
	char instruction[MAX_INSTRUCTION_SIZE] = {0};
	int index = 0;
	while(s[index] != ' '){
		instruction[index] = s[index];
		index++;
	}

	//Declaration du tableau des types I
	char *typeRInstruction[]={
		"ADD"	
	};

	//Declaration du tableau des types I
	char *typeIInstruction[]={
		"ADDI"
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
		exit(1);
	}

	return toReturnType;
}

int getIsSpecial(const char *s){
	
	int isSpecial = 0;

	//Declaration du tableau des spécials
	char *specialInstructions[] = {
		"ADD"
	};

	//Copier l'instruction
	char instruction[MAX_INSTRUCTION_SIZE] = {0};
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