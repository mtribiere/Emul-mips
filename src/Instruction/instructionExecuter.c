#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "memoryManager.h"
#include "Instruction/instructionInfo.h"
#include "Instruction/instructionExecuter.h"

//Executer les instructions en fonction de leur type
void executeInstruction(char *instruction,ProcRegister *registers){

	//Récuperer le type de l'instruction
	char instructionType[MAX_INSTRUCTION_LENGTH] = {0};
	for(int i = 0;instruction[i] != ' ';i++) instructionType[i] = instruction[i];

	//////On verifie toutes les instructions supportées
	//ADD
	if(strcmp(instructionType,"ADD") == 0){
		printf("Instruction ADD\n");
		ADD(getOperandeWithPosition(instruction,1),getOperandeWithPosition(instruction,2),getOperandeWithPosition(instruction,3),registers);
	}else{
		printf("Instruction non supportée\n");
	}
	
	//Passer à l'instruction suivante
	storeInRegister(loadFromRegister(REGISTER_COUNT-1,*registers)+1,REGISTER_COUNT-1,registers);

}

//Exemple de fonction ADD (sans gestion de débordement)
void ADD(int destinationRegister,int operandeRegister1,int operandeRegister2, ProcRegister *registers){

	//Prendre les deux opérandes
	long int a = loadFromRegister(operandeRegister1,*registers);
	long int b = loadFromRegister(operandeRegister2,*registers);

	//Faire l'addition
	long int result = a+b;

	//Stocker le résultat
	storeInRegister(result,destinationRegister,registers);

}