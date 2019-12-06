#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileInstructions.h"
#include "utils.h"


int main(void)
{
	int index;

	char *instruction;
	instruction=malloc(50*sizeof(char));

	char *opcode;
	opcode=malloc(6*sizeof(char));

	printf("\n========== Emul-mips qui claque ===========\n");

/*	
	printf("Taille code opération : %d\n\n",getOperationSize("ADDI $2,$2,3"));

	printf("Nombre d'instruction dans le fichier in.txt : %d\n\n",getInstructionCount("../testFiles/in.txt"));
*/
	readInstructionInFile("../testFiles/test_ADD.txt", 2, instruction);
	printf("Instruction numéro 2 du fichier test_ADD.txt : %s\n\n",instruction);

	writeInstructionInFile("../testFiles/test_ADD.txt", 3, instruction);

	printf("Instruction numéro 4 du fichier test_ADD.txt : ");
	readInstructionInFile("../testFiles/test_ADD.txt", 4, instruction);
	printf("%s\n\n",instruction);

	getOperationCode(instruction,opcode);
	printf("Code opération : \n");
	for(index=0;index<6;index++) printf("%c",opcode[index]);
	printf("\n\n Fin affichage \n\n");

	return 0;
	//printf("Conversion hexa to binary : %s \n\n",convertHexaToBinary("2"));
}
