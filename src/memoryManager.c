#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "memoryManager.h"

void initializeRegister(int size,ProcRegister *registers)
{
    registers->memorySize = size;
	registers->mem = malloc(sizeof(long int)*size);
}

void initializeMemory(int size, MainMemory *memory)
{
    memory->memorySize = size;
	memory->mem = malloc(sizeof(int)*(size));
}

long int loadFromRegister(int index, ProcRegister registers){
	//Verifier que le registre existe
	checkRegisterIndex(index);

	//Retourner le contenu du registre
	return ((registers.mem)[index]);
}

void storeInRegister(long int toStore, int index, ProcRegister *registers){
	//Verifier que le registre existe
	checkRegisterIndex(index);

	//Placer la données
	(registers->mem[index]) = toStore;
}


long int loadFromMemory(int index, MainMemory memory){
	
	long int toReturn;
	char toReturnBinary[32] = {0};

	//Pour les 4 emplacements mémoires
	for(int i = 0;i<4;i++){
		//Verifier que l'emplacement existe
		checkMemoryAddress(index+i);

		//Ajouter à la fin de la chaine
		char temp[9] = {0};
		convertToBinarySized((memory.mem)[index+i],temp,8);

		appendStr(temp,toReturnBinary);  		
	}
	
	toReturn = convertBinToInt(toReturnBinary,32);

	return toReturn;
}

void storeInMemory(long int toStore, long int index, MainMemory *memory){

	//Convertir en binaire le chiffre
	char binary[32] = {0};
	convertToBinarySized(toStore,binary,32);
	int currentPart = 0;

	//Pour chaque index de bébut d'octet
	for(int i = 0; i<32 ;i+=8){

		//Verifier que l'emplacement existe
		checkMemoryAddress(index+currentPart);

		//Copier dans un tableau temporaire
		char temp[8] = {0};
		for(int j = 0;j<8;j++){
			temp[j] = binary[i+j]; 
		}

		//Stocker
		(memory->mem)[index+currentPart] = convertBinToInt(temp,8);

		//Passer à la partie suivante
		currentPart++;
		
	}

	
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

void checkMemoryAddress(int index){
	//Verification
	if(index < 0 || index >= MAIN_MEMORY_SIZE){
		printf("Erreur : L'emplacement mémoire %d n'existe pas\n",index);
		exit(4);
	}
}