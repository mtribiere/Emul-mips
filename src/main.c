#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "Instruction/instructionTable.h"

int main(void)
{
	////////////////////Definition de l'instruction set
	
	char *instructionSet[INSTRUCTION_SET_SIZE] = {"ADDI","ADD"};
	
	instructionTable instructionInfos[INSTRUCTION_SET_SIZE] = {
		{0,8}, 		//ADDI
		{1,32} 		//ADD
	};



	/////////////////////Lancer l'émulateur
	printf("\n========== Emul-mips qui claque ===========\n");
	
	printf("Taille code opération : %d\n\n",getOperationSize("ADDI $2,$8,3"));
	
	char buff[8];
	buff[7] = '\0';
	convertToBinarySized("125",buff,7);
	printf("Binaire à taille fixe: %s\n",buff);

	return 0;
}
