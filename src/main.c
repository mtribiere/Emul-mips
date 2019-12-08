#include <stdio.h>
#include <stdlib.h>
#include "Instruction/instructionConverter.h"
#include "Instruction/instructionInfo.h"
#include "fileManager.h"
#include "utils.h"

#define MAX_PROGRAM_LENGTH 50
#define MAX_INSTRUCTION_LENGTH 50


/****
 * Instructions supportées
 * 
 * Arithmetic : 
 * ADDI
 * ADD
 * SUB
 * 
 * Logical : 
 * AND
 * OR
 * 
 * 
 * ***/

int main(int argc, char *argv[])
{
	/////////////////////Recuperer les instructions
	//Si pas de fichiers fourni
	if(argc < 3){
		printf("Usage ./emul-mips Fichier_source Fichier_destination\n");
		exit(1);
	}

	//Creer le tableau de toutes les instructions
	char *instructions[MAX_PROGRAM_LENGTH] = {0};
	for(int i = 0;i<MAX_PROGRAM_LENGTH;i++){
		instructions[i] = malloc(sizeof(char)*MAX_INSTRUCTION_LENGTH);
		instructions[i][MAX_INSTRUCTION_LENGTH-1] = '\0';
	}

	//Charger toutes les instructions
	int instructionCount = getInstructionCount(argv[1]);
	for(int i = 0;i<instructionCount;i++){
		readInstructionInFile(argv[1],i,instructions[i]);
	}

	/////////////////////Lancer l'émulateur
	printf("\n========== Emul-mips qui claque ===========\n");
	
	printf("\nNombre d'instruction : %d\n\n",instructionCount);

	//Pour toutes les instructions
	for(int i = 0;i<instructionCount;i++){
		
		char instructionHex[9] = {0};
		instructionHex[8] = '\0';

		instructionToHex(instructions[i],instructionHex);

		printf("Instruction %d : %s\n",i,instructionHex);

	}
	printf("\n");
  	
	////////////////////Liberer la memoire
	for(int i = 0;i<MAX_PROGRAM_LENGTH;i++)
		free(instructions[i]);


	return 0;
}