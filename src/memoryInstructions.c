#include <stdio.h>
#include <stdlib.h>
#include "memoryInstructions.h"

/*
void printer(registre *myRegister)
*/

void initializeRegister(registre *myRegister)
{
    int index_line;
    int index_column;

    (*myRegister).nbInstructionsInside=0;

    for(index_line=0;index_line<REGISTER_SIZE;index_line++)
    {
    	for (index_column=0;index_column<32;index_column++)
	    {
		    ((*myRegister).instructions)[index_line][index_column]='0';
	    }
	    ((*myRegister).instructions)[index_line][index_column]='\0';
    }
}

void initializeMemory(memory *myMemory)
{
    int index_line;
    int index_column;

    (*myMemory).nbInstructionsInside=0;
    
    for (index_line=0;index_line<MEMORY_SIZE;index_line++)
    {
        for(index_column=0;index_column<32;index_column++)
        {
            ((*myMemory).instructions)[index_line][index_column]='0';
        }
        ((*myMemory).instructions)[index_line][index_column]='\0';
    }
}

/* load <=> write  store <=> read & return */

void loadIntoRegister(char *instruction, registre *myRegister)
{
    int index;
    for (index=0;index<32;index++)
    {
        ((*myRegister).instructions)[(*myRegister).nbInstructionsInside][index]=instruction[index];
        printf("\n %d : %c\n",index,((*myRegister).instructions)[(*myRegister).nbInstructionsInside][index]);

    }
    ((*myRegister).instructions)[(*myRegister).nbInstructionsInside][index]='\0';
    (*myRegister).nbInstructionsInside++;
}

void loadIntoMemory(char *instruction, memory *myMemory)
{
    int index;
    for (index=0;index<32;index++)
    {
        ((*myMemory).instructions)[(*myMemory).nbInstructionsInside][index]=instruction[index];
        //printf("\n %d : %c\n",index,((*myMemory).instructions)[(*myMemory).nbInstructionsInside][index]);
    }
    ((*myMemory).instructions)[(*myMemory).nbInstructionsInside][index]='\0';
    (*myMemory).nbInstructionsInside++;
}

/* charge dans *instruction l'instruction présente dans le registre à l'indice indexInstruction */
void storeIntoRegister(char *instruction, int indexInstruction, registre *myRegister)
{
    int index;
    for (index=0;index<32;index++)
    {
        //printf("\n Index : %d \n",index);
        instruction[index]=((*myRegister).instructions)[indexInstruction][index];
    }
    instruction[index]='\0';
    /* Supprimer l'instruction du registre ? Si oui, faire l'instruction suivante : */
    /*(*myRegister).nbInstructionsInside--;*/
}


/* charge dans *instruction l'instruction présente dans la mémoire à l'indice indexInstruction */
void storeIntoMemory(char *instruction, int indexInstruction, memory *myMemory)
{
    int index;
    for (index=0;index<32;index++)
    {
        //printf("\n Index : %d \n",index);
        instruction[index]=((*myMemory).instructions)[indexInstruction][index];
    }
    instruction[index]='\0';
    /* Supprimer l'instruction de la mémoire ? Si oui, faire l'instruction suivante : */
    /*(*myMemory).nbInstructionsInside--;*/
}