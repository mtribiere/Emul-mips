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
	////////////////////Afficher la bannière
	printf("============== Emul-mips : DAUTREY Marin RIBIERE Matthieu ============\n");

	///////////////////Choisir le mode d'execution
	/*Mode : 
	 * 	0 : Fonctionnement normal
	 * 	1 : Mode pas à pas
	 * 	2 : Mode interactif
	 * **/

	//Si pas d'arguments fourni
	if(argc < 3 && argc != 1){
		printf("Usage : ./emul-mips Fichier_source Fichier_destination\n");
		printf("Utilisez --pas A LA FIN pour le mode pas à pas\n");
		printf("Ou ./emul-mips pour le mode interactif\n");
		exit(1);
	}

	int mode = 0;

	//Si on doit entrer en mode pas à pas
	if(argc == 1)
		mode = 2;

	//Si on doit entrer en mode pas à pas
	if(argc == 4){
		if(strcmp("--pas",argv[3]) == 0){
			mode = 1;
		}else{
			printf("Unrecognized arguement : %s\nExiting\n",argv[3]);
			exit(1);
		}
	}

	//DEBUG
	/*
	for(int i = 0;i<argc;i++)
		printf("Arg %d : %s\n",i,argv[i]);
	*/


	//Si on est en mode de fonctionnement normal ou pas à pas
	if(mode == 0 || mode == 1){

		/////////////////////Recuperer les instructions
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

		//DEBUG
		/*	
		storeInMemory(0x1,8,&mainMemory);
		storeInMemory(0x2,12,&mainMemory);
		storeInMemory(0x3,16,&mainMemory);
		storeInMemory(0x4,20,&mainMemory);
		storeInRegister(8,4,&registers);
		*/
		//Tant qu'on a pas atteint la fin du programme
		while(loadFromRegister(PC_REGISTER,registers) < instructionCount){

			//Si on est en mode pas a pas
			if(mode == 1){

				//Effacer l'écran 
				for(int i = 0;i<100;i++) printf("\n");


				//Afficher les instructions
				printProgramForStepMode(instructions,instructionCount,loadFromRegister(PC_REGISTER,registers));
			}
			
			//Executer l'instruction
			executeInstruction(instructions[loadFromRegister(PC_REGISTER,registers)],&registers,&mainMemory,labelTable);

			//Passer à l'instruction suivante
			storeInRegister(loadFromRegister(PC_REGISTER,registers)+1,PC_REGISTER,&registers);

			//Afficher l'état des registres
			printf("=== Registres ===\n");
			printRegisters(registers);

			//Afficher l'état de la mémoire
			printf("=== Mémoire principale ===\n");
			printMainMemory(mainMemory);

			//Si on est en mode pas a pas
			if(mode == 1){

				//Attendre l'appui sur entree
				printf("\n === Press enter to continue ===\n");
				while(getchar() != '\n');

			}else{ //Si on est en mode normal
				printf("\n\n========================== ");
			}
		}


		printf("=== Fin de l'execution === \n");

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

	//Si on est en mode interactif
	if(mode == 2){
		printf("Aucun fichier fourni, passage en mode interactif : \n");

		//////////////////////Initialisation du mode interactif
		//Creer les registres
		ProcRegister registers;
		initializeRegister(REGISTER_COUNT,&registers);

		//Creer la mémoire principale
		MainMemory mainMemory;
		initializeMemory(MAIN_MEMORY_SIZE,&mainMemory);

		int needExit = 0;
		char currentInstruction[MAX_INSTRUCTION_LENGTH] = {0};

		/////////////////////Lancer la console
		//Tant que qu'on ne doit pas quitter
		while(!needExit){

			//Afficher le padding
			printf("\n\n\n\n\n\n=============\n");

			//Afficher les registres
			printRegisters(registers);
			
			//Afficher la memoire
			printMainMemory(mainMemory);
			
			//Entrer l'instruction
			printf(">>>");
			fgets(currentInstruction,MAX_INSTRUCTION_LENGTH,stdin);

			//Formater l'instruction
			int i = 0;
			while(currentInstruction[i] != '\n')
				i++;
			currentInstruction[i] = '\0';

			//Si l'instruction est EXIT
			if(strcmp(currentInstruction,"EXIT") == 0){
				needExit = 1;
			}else{ // Si c'est une instuction classique

					//Executer la commande
					executeInstruction(currentInstruction,&registers,&mainMemory,NULL);
			}		
		}

		printf("\n=== Fin de l'éxecution ===\n");
		/////////////////Liberer la mémoire
		freeRegisters(&registers);
		freeMainMemory(&mainMemory);


	}

	return 0;
}