#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "memoryManager.h"
#include "Instruction/instructionInfo.h"
#include "Instruction/mipsInstructions.h"
#include "Instruction/instructionExecuter.h"

//Executer les instructions en fonction de leur type
void executeInstruction(char *instruction,ProcRegister *registers){

	//Récuperer le type de l'instruction
	char instructionType[MAX_INSTRUCTION_LENGTH] = {0};
	for(int i = 0;instruction[i] != ' ';i++) instructionType[i] = instruction[i];

	//////On verifie toutes les instructions supportées
	//ADD
	if(strcmp(instructionType,"ADD") == 0){
		ADD(getOperandeWithPosition(instruction,1),getOperandeWithPosition(instruction,2),getOperandeWithPosition(instruction,3),registers);
	}
	//ADDI
	else if(strcmp(instructionType,"ADDI") == 0){
		ADDI(getOperandeWithPosition(instruction,2),getOperandeWithPosition(instruction,1),getOperandeWithPosition(instruction,3),registers);
	}

	//SUB
	else if(strcmp(instructionType,"SUB") == 0){
		SUB(getOperandeWithPosition(instruction,1),getOperandeWithPosition(instruction,2),getOperandeWithPosition(instruction,3),registers);
	}

	//AND
	else if(strcmp(instructionType,"AND") == 0){
		AND(getOperandeWithPosition(instruction,1),getOperandeWithPosition(instruction,2),getOperandeWithPosition(instruction,3),registers);
	}

	//OR
	else if(strcmp(instructionType,"OR") == 0){
		OR(getOperandeWithPosition(instruction,1),getOperandeWithPosition(instruction,2),getOperandeWithPosition(instruction,3),registers);
	}
	
	//XOR
	else if(strcmp(instructionType,"XOR") == 0){
		XOR(getOperandeWithPosition(instruction,1),getOperandeWithPosition(instruction,2),getOperandeWithPosition(instruction,3),registers);
	}

	//Instruction non supportée
else{
		printf("Instruction non supportée\n");
	}
	
	//Passer à l'instruction suivante
	storeInRegister(loadFromRegister(REGISTER_COUNT-1,*registers)+1,REGISTER_COUNT-1,registers);
}