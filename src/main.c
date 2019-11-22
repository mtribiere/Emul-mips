#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "Instruction/ADDI.h"

int main(void)
{
	printf("\n========== Emul-mips qui claque ===========\n");
	
	printf("Taille code opération : %d\n\n",getOperationSize("ADDI $2,$8,3"));

	return 0;
}
