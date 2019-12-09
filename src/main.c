#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Instruction/instructionConverter.h"
#include "Instruction/instructionInfo.h"
#include "fileManager.h"
#include "utils.h"


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
 * Branching:
 * BEQ
 * BNE
 * 
 *****/

int main(int argc, char *argv[])
{
	/////////////////////Recuperer les instructions
	//Si pas d'arguments fourni
	if(argc < 3){
		printf("Usage : ./emul-mips Fichier_source Fichier_destination\n");
		exit(1);
	}

	//Creer le tableau de toutes les instructions
	char *instructions[MAX_PROGRAM_LENGTH] = {0};
	for(int i = 0;i<MAX_PROGRAM_LENGTH;i++){
		instructions[i] = malloc(sizeof(char)*MAX_INSTRUCTION_LENGTH);
		instructions[i][MAX_INSTRUCTION_LENGTH-1] = '\0';
	}

	//Charger toutes les instructions
	int instructionCount = loadInstructionfromFile(argv[1],instructions);

	//Creer un tableau pour toutes les instructions en hexa
	char *instructionsHex[instructionCount];
	for(int i = 0;i<instructionCount;i++){
		instructionsHex[i] = malloc(sizeof(char)*INSTRUCTION_HEX_LENGTH);
		instructionsHex[i][INSTRUCTION_HEX_LENGTH-1] = '\0';
	}

	/////////////////////Lancer l'émulateur
	printf("\n========== Emul-mips - Marin Dautrey - Matthieu Ribiere ===========\n");

	printf("\nNombre d'instruction : %d\n\n",instructionCount);

	//Pour toutes les instructions
	for(int i = 0;i<instructionCount;i++){
		
		//Convertir
		char instructionHex[INSTRUCTION_HEX_LENGTH] = {0};
		instructionToHex(instructions[i],instructionHex);

		//DEBUG
		/*int j = 0;
		while(instructions[i][j] != '\0'){
			printf(" %d ",instructions[i][j]);
			j++;
		}
		printf("\n");*/

		//Afficher
		printf("%d : %s -> %s\n",i,instructions[i],instructionHex);

		//Stocker
		strcpy(instructionsHex[i],instructionHex);

	}
	printf("\n");

	//////////////////Stocker les instructions
	writeInstructionInFile(argv[2],instructionsHex,instructionCount);
  	
	////////////////////Liberer la memoire
	for(int i = 0;i<MAX_PROGRAM_LENGTH;i++)
		free(instructions[i]);

	for(int i = 0;i<instructionCount;i++)
		free(instructionsHex[i]);

	return 0;
}