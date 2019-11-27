#include <stdio.h>
#include <stdlib.h>
#include "Instruction/instructionConverter.h"
#include "utils.h"

int main(void)
{
	/////////////////////Lancer l'émulateur
	printf("\n========== Emul-mips qui claque ===========\n");
	
	printf("Taille code opération : %d\n\n",getOperationSize("ADDI $2,$8,3"));
	
	char instructionBinary[33]={0};
	instructionBinary[32] = '\0';
	operationToBinary("ADDI $8,$4,5",1,0,instructionBinary);

	printf("Convertion en binaire : %s\n",instructionBinary);
	
	return 0;
}
