#include <stdio.h>
#include <stdlib.h>
#include "Instruction/instructionConverter.h"
#include "utils.h"

int main(void)
{
	/////////////////////Lancer l'émulateur
	printf("\n========== Emul-mips qui claque ===========\n");
	
	printf("Taille code opération : %d\n\n",getOperationSize("ADDI $2,$8,3"));
	
	char instructionHex[9] = {0};
	instructionHex[8] = '\0';

	instructionToHex("ADDI $2,$3,200",instructionHex);

	printf("Convertion en hexa : %s\n",instructionHex);
	
	return 0;
}
