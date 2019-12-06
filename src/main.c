#include <stdio.h>
#include <stdlib.h>
#include "Instruction/instructionConverter.h"
#include "Instruction/instructionInfo.h"
#include "utils.h"



/****
 * Instructions supportées
 * 
 * ADDI
 * ADD
 * 
 * ***/

int main(void)
{
	/////////////////////Lancer l'émulateur
	printf("\n========== Emul-mips qui claque ===========\n");
	
	char instructionHex[9] = {0};
	instructionHex[8] = '\0';

	instructionToHex("ADDI $78,$12,$20",instructionHex);

	printf("Convertion en hexa : %s\n\n",instructionHex);

	return 0;
}
