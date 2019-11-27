#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main(void)
{
	char *instruction;
	instruction=malloc(sizeof(instruction));

	printf("\n========== Emul-mips qui claque ===========\n");

/*	
	printf("Taille code opération : %d\n\n",getOperationSize("ADDI $2,$2,3"));

	printf("Nombre d'instruction dans le fichier in.txt : %d\n\n",getInstructionCount("../testFiles/in.txt"));
*/
	readInstructionInFile("../testFiles/in.txt", 2, instruction);
	printf("Instruction numéro 2 du fichier in.txt : %s\n\n",instruction);

	writeInstructionInFile("../testFiles/in.txt", 3, instruction);

	printf("Instruction numéro 3 du fichier in.txt : ");
	readInstructionInFile("../testFiles/in.txt", 3, instruction);
	printf("%s\n\n",instruction);

	return 0;
	//printf("Conversion hexa to binary : %s \n\n",convertHexaToBinary("2"));
}
