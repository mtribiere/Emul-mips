/*******************************************************/
/*Fichier contenants des fonctions d'utilité (convertion, calcul de taille,....)*/
/******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileInstructions.h"

/* Prend en paramètres une instruction TERMINEE PAR UN ' ' ex. "ADDI " */
/* Charge l'opcode de cette instruction ex. 001000 dans le tableau opcode */
void getOperationCode(char *instruction, char *opcode)
{
	int index=0;
	int size=0;

	char *instruction_tmp;

	/* Calcule de la taille à allouer */

	while(instruction[size]!=' ')
	{
		size++;	
	}
	instruction_tmp=malloc(size*sizeof(char));

	for(index=0; index < size; index++) instruction_tmp[index]=instruction[index];
	instruction_tmp[size]='\0';
	for(index=0;index<6;index++) opcode[index]=0;

	//printf("\n\n%d %s %d %d %d\n\n",size, instruction_tmp,strcmp(instruction,"AND\0"),strcmp("AND\0","AND\0"),memcmp(instruction_tmp,"AND\0",size));

	if(memcmp(instruction_tmp,"ADD\0",size)==0) strcpy(opcode,"100000");
	else if(memcmp(instruction,"ADDI\0",size)==0) strcpy(opcode,"001000");
	else if(memcmp(instruction,"AND\0",size)==0) strcpy(opcode,"100100");

	else if(memcmp(instruction,"BEQ\0",size)==0) strcpy(opcode,"000100");
	else if(memcmp(instruction,"BNE\0",size)==0) strcpy(opcode,"000101");
	else if(memcmp(instruction,"BLEZ\0",size)==0) strcpy(opcode,"000110");
	else if(memcmp(instruction,"BGTZ\0",size)==0) strcpy(opcode,"000111");


	else if(memcmp(instruction,"DIV\0",size)==0) strcpy(opcode,"011010");
	else if(memcmp(instruction,"J\0",size)==0) strcpy(opcode,"000010");
	else if(memcmp(instruction,"JAL\0",size)==0) strcpy(opcode,"000011");
	else if(memcmp(instruction,"JR\0",size)==0) strcpy(opcode,"001000");

	else if(memcmp(instruction,"LUI\0",size)==0) strcpy(opcode,"001111");
	else if(memcmp(instruction,"LW\0",size)==0) strcpy(opcode,"100011");

	else if(memcmp(instruction,"MFHI\0",size)==0) strcpy(opcode,"010000");
	else if(memcmp(instruction,"MFLO\0",size)==0) strcpy(opcode,"010010");
	else if(memcmp(instruction,"MULT\0",size)==0) strcpy(opcode,"011000");

	else if(memcmp(instruction,"NOP\0",size)==0) strcpy(opcode,"000000");
	else if(memcmp(instruction,"OR\0",size)==0) strcpy(opcode,"100101");
	else if(memcmp(instruction,"ROTR\0",size)==0) strcpy(opcode,"000010");

	else if(memcmp(instruction,"SLL\0",size)==0) strcpy(opcode,"000000");
	else if(memcmp(instruction,"SLT\0",size)==0) strcpy(opcode,"101010");
	else if(memcmp(instruction,"SRL\0",size)==0) strcpy(opcode,"000010");
	else if(memcmp(instruction,"SUB\0",size)==0) strcpy(opcode,"100010");
	
	else if(memcmp(instruction,"SW\0",size)==0) strcpy(opcode,"101011");
	else if(memcmp(instruction,"SYSCALL\0",size)==0) strcpy(opcode,"001100");
	else if(memcmp(instruction,"XOR\0",size)==0) strcpy(opcode,"100110");
}


/* Fonction qui calcule le nombre d'opérations dans un fichier */
int getInstructionCount(char *nameFile)
{
	FILE *fileIn;

	int nbLine=0;
	char charRead;

	fileIn=fopen(nameFile,"r");
	if(fileIn==NULL) printf("Erreur lors de l'ouverture du fichier en entrée.\n\n");
	else
	{
		charRead=fgetc(fileIn);
		while(charRead != EOF)
		{
			//printf("\nDébut de la boucle \n\n");
			if(charRead=='\n') nbLine++;
			charRead=fgetc(fileIn);
			//printf(" nbLine : %d	charRead : %c char attendu : %c \n\n",nbLine,charRead,'\\');
			//printf("\nFin de la boucle \n\n");
		}
	}

	return nbLine;
}

/* Fonction qui lit l'instruction n°id dans le fichier fourni et la load dans instruction */
void readInstructionInFile(char *nameFile, int id, char *instruction)
{
	FILE *fileIn;
	char charRead;

	int nbLine=0;
	int indexInstruction=0;

	fileIn=fopen(nameFile,"r");
	if(fileIn==NULL)
	{
		printf("Erreur lors de l'ouverture du fichier en entrée.\n\n");
		instruction=NULL;
	}
	else
	{
		charRead=fgetc(fileIn);
		//printf("Entrée dans la boucle ok \n\n");
		
		while(charRead!=EOF && nbLine!=id)
		{
			if(charRead=='\n') nbLine++;
			charRead=fgetc(fileIn);
			//printf(" nbLine : %d	charRead : %c \n\n",nbLine,charRead);
		}

		if(nbLine==id)
		{
			while(charRead!='\n')
			{
				instruction[indexInstruction]=charRead;
				indexInstruction++;
				charRead=fgetc(fileIn);
				//printf(" indexInstruction : %d	charRead : %c \n\n",nbLine,charRead);
			}
		}
		
	}
	fclose(fileIn);
}

/* Fonction qui écrit l'instruction donnée dans le fichier fourni à la ligne n°id */
/* ATTENTION : l'instruction doit se terminer par \0\n */
void writeInstructionInFile(char *nameFile, int id, char *instruction)
{
	FILE *fileIn;
	char charRead;

	int nbLine=0;

	/* Une ouverture de fichier en r+ paermet malgré tout d'écrire dedans!! */
	fileIn=fopen(nameFile,"r+");
	if(fileIn==NULL)
	{
		printf("Erreur lors de l'ouverture du fichier en entrée.\n\n");
		instruction=NULL;
	}
	else
	{
		charRead=fgetc(fileIn);
		//printf("Entrée dans la boucle ok \n\n");

		while(charRead!=EOF && nbLine!=id)
		{
			if(charRead=='\n') nbLine++;
			if(nbLine!=id) charRead=fgetc(fileIn);
			//printf(" nbLine : %d	charRead : %c \n\n",nbLine,charRead);
		}

		if(nbLine==id)
		{
			//printf("Destination atteinte !! \n\n");
			fputs(instruction,fileIn);
		}
	}
	fclose(fileIn);
}


/* Prend en entrée une string source de longueur src_size de caractères hexa */
/* Ecrit le résultat converti en binaire dans la string de destination */
/*
char *convertHexaToBinary(char *string, int src_size, char *stringDest)
{
	long int index=0;
	char toReturn[9]={0,0,0,0,0,0,0,0,'\0'};

    while(string[index]!='\0')
    {
        switch(string[index])
        {
            case '0': printf("0000"); break;
            case '1': printf("0001"); break;
            case '2': printf("0010"); break;
            case '3': printf("0011"); break;
            case '4': printf("0100"); break;
            case '5': printf("0101"); break;
            case '6': printf("0110"); break;
            case '7': printf("0111"); break;
            case '8': printf("1000"); break;
            case '9': printf("1001"); break;
            case 'A': printf("1010"); break;
            case 'B': printf("1011"); break;
            case 'C': printf("1100"); break;
            case 'D': printf("1101"); break;
            case 'E': printf("1110"); break;
            case 'F': printf("1111"); break;
            case 'a': printf("1010"); break;
            case 'b': printf("1011"); break;
            case 'c': printf("1100"); break;
            case 'd': printf("1101"); break;
            case 'e': printf("1110"); break;
            case 'f': printf("1111"); break;
			default: printf("Erreur : %c n'est pas un caractère hexadécimal connu.",string[index]);
		}
		printf("\n\n");
	}

	return toReturn;
}
*/