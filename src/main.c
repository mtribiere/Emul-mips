#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main(void)
{
	printf("\n========== Emul-mips qui claque ===========\n");
	
	printf("Taille code opération : %d\n\n",getOperationSize("ADDI $2,$2,3"));


	return 0;
}
