#include <stdio.h>
#include <stdlib.h>
#include "memoryManager.h"

void initializeRegister(int size,ProcRegister *registers)
{
    registers->memorySize = size;
	registers->mem = malloc(sizeof(int)*size);
}

void initializeMemory(int size, MainMemory *memory)
{
    memory->memorySize = size;
	memory->mem = malloc(sizeof(int)*size);
}

int loadFromRegister(int index, ProcRegister registers){
	//Verifier que le registre existe
	checkRegisterIndex(index);

	//Retourner le contenu du registre
	return ((registers.mem)[index]);
}

void storeInRegister(int toStore, int index, ProcRegister *registers){
	//Verifier que le registre existe
	checkRegisterIndex(index);

	//Placer la données
	(registers->mem[index]) = toStore;
}


void freeRegisters(ProcRegister *registers){
	registers->memorySize = 0;
	free(registers->mem);
}

void freeMainMemory(MainMemory *memory){
	memory->memorySize = 0;
	free(memory->mem);
}

void checkRegisterIndex(int index){
	
	//Verification du registre
	if(index < 0 || index >= REGISTER_COUNT){
		printf("Erreur : Le registe %d n'existe pas\n",index);
		exit(3);
	}

}