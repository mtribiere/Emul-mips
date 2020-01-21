#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Instruction/instructionConverter.h"
#include "Instruction/instructionInfo.h"
#include "Instruction/instructionExecuter.h"
#include "fileManager.h"
#include "memoryManager.h"
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
 * BGTZ
 * BLEZ
 * 
 *****/

int main(int argc, char *argv[])
{
	/*Mode : 
	 * 	0 : Fonctionnement normal
	 * 	1 : Mode pas à pas
	 * 	2 : Mode interactif
	 * **/
	int mode = 0;

	if(argc == 1)
		mode = 2;

	/////////////////////Recuperer les instructions
	//Si pas d'arguments fourni
	if(argc < 3 && argc != 1){
		printf("Usage : ./emul-mips Fichier_source Fichier_destination\n");
		printf("Utilisez -pas pour le mode pas à pas\n");
		printf("Ou ./emul-mips pour le mode interactif\n");
		exit(1);
	}

	//Si on est en mode de fonctionnement normal ou pas à pas
	if(mode == 0 || mode == 1){
		//Creer le tableau de toutes les instructions
		char *instructions[MAX_PROGRAM_LENGTH] = {0};
		initializeStringArray(instructions,MAX_PROGRAM_LENGTH,MAX_INSTRUCTION_LENGTH);

		//Charger toutes les instructions
		int instructionCount = loadInstructionfromFile(argv[1],instructions);

		//Creer un tableau de tout les noms de label
		char *labelTable[MAX_PROGRAM_LENGTH] = {0};
		initializeStringArray(labelTable,MAX_PROGRAM_LENGTH,MAX_LABEL_NAME_LENGTH);

		//Formater les instructions
		formatInstructions(instructions,instructionCount,labelTable);

		//Creer un tableau pour toutes les instructions en hexa
		char *instructionsHex[instructionCount];
		initializeStringArray(instructionsHex,instructionCount,INSTRUCTION_HEX_LENGTH);
	
		//Creer les registres
		ProcRegister registers;
		initializeRegister(REGISTER_COUNT,&registers);

		//Creer la mémoire principale
		MainMemory mainMemory;
		initializeMemory(MAIN_MEMORY_SIZE,&mainMemory);

		/////////////////////Lancer l'émulateur
		printf("\n========== Emul-mips - Marin Dautrey - Matthieu Ribiere ===========\n");

		printf("\nNombre d'instruction : %d\n\n",instructionCount);

		///////////////Partie convertion
		for(int i = 0;i<instructionCount;i++){
			
			//Convertir en hexa
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
		printf("\n\n");

		////////////Partie emulation

		//Initialiser le PC
		storeInRegister(0,PC_REGISTER,&registers);

		//Tant qu'on a pas atteint la fin du programme
		while(loadFromRegister(PC_REGISTER,registers) < instructionCount){

			//Executer l'instruction
			executeInstruction(instructions[loadFromRegister(PC_REGISTER,registers)],&registers,&mainMemory,labelTable);

			//Afficher l'état des registres
			printRegisters(registers);
		}


		printf("\n");

		//////////////////Stocker les instructions 
		writeInstructionInFile(argv[2],instructionsHex,instructionCount);

		//////////////////TEST
		//storeInRegister(0xC1B4,4,&registers);
		//printf("Load from Register : %d\n\n",loadFromRegister(4,registers));
		//storeInMemory(0x54D24B21,0x4,&mainMemory);
		//storeInMemory(0x1F,0x4,&mainMemory);
		//(mainMemory.mem[2]) = 0xFF;
		//printf("Load from Memory : %d\n",loadFromMemory(0,mainMemory));
		//printMainMemory(mainMemory);

		////////////////////Liberer la memoire
		//Pour les instructions
		for(int i = 0;i<MAX_PROGRAM_LENGTH;i++)
			free(instructions[i]);

		//Pour les instructions Hexa
		for(int i = 0;i<instructionCount;i++)
			free(instructionsHex[i]);

		//Pour les registres
		freeRegisters(&registers);

		//Pour la memoire principale
		freeMainMemory(&mainMemory);

	}

	if(mode == 2){
		char currentInstruction[MAX_INSTRUCTION_LENGTH] = {0};
		printf("Aucun fichier fourni, passage en mode interactif : \n");
		printf(">>>\n");
	}

	return 0;
}