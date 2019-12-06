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
	int index;

	for(index=0;index<6;index++) opcode[index]=0;

	if(strcmp(instruction,"ADD")) strcpy(opcode,"100000");
	if(strcmp(instruction,"AND")) strcpy(opcode,"100100");
	if(strcmp(instruction,"SUB")) strcpy(opcode,"100010");
	if(strcmp(instruction,"OR")) strcpy(opcode,"100101");
	if(strcmp(instruction,"XOR")) strcpy(opcode,"100110");
	if(strcmp(instruction,"SLT")) strcpy(opcode,"101010");
	if(strcmp(instruction,"NOP")) strcpy(opcode,"000000");
	if(strcmp(instruction,"SLL")) strcpy(opcode,"000000");
	if(strcmp(instruction,"SRL")) strcpy(opcode,"000010");
	if(strcmp(instruction,"ROTR")) strcpy(opcode,"000010");
	if(strcmp(instruction,"JR")) strcpy(opcode,"001000");
	if(strcmp(instruction,"MFHI")) strcpy(opcode,"010000");
	if(strcmp(instruction,"MFLO")) strcpy(opcode,"010010");
	if(strcmp(instruction,"MULT")) strcpy(opcode,"011000");
	if(strcmp(instruction,"DIV")) strcpy(opcode,"011010");
	if(strcmp(instruction,"SYSCALL")) strcpy(opcode,"001100");

	if(instruction[0]=='J')
	{
		if(instruction[1]=='R') opcode[2]=1;
		else
		{
			opcode[4]=1;
			if(instruction[1]=='A' && instruction[2]=='L') opcode[5]=1;
			/* Condition 1 fausse implique condition 2 non évaluée (ici problème ssi instruction[1]=' ')*/
		}
	}

	if(instruction[0]=='B')
	{
		opcode[3]=1;
		if(instruction[1]=='N'&& instruction[2]=='E') opcode[5]=1;
		if(instruction[1]=='L' && instruction[2]=='E' && instruction[3]=='Z') opcode[4]=1;
		if(instruction[1]=='G' && instruction[2]=='T' && instruction[3]=='Z')
		{
			opcode[4]=1;
			opcode[5]=1;
		}
	}

	//if(instruction[0]=='A' && instruction[1]=='D' && instruction[2]=='D' && instruction[3]==' ') opcode[0]=1;
	//if(instruction[0]=='A' && instruction[1]=='D' && instruction[2]=='D' && instruction[3]=='I') opcode[2]=1;

	if(instruction[0]=='A' && instruction[1]=='N' && instruction[2]=='D' && instruction[3]==' ')
	{
		opcode[2]=1;
		opcode[5]=1;
	}

	if((instruction[0]=='L' || instruction[0]=='S') && instruction[1]=='W')
	{
		opcode[0]=1;
		opcode[2]=1;
		opcode[4]=1;
		opcode[5]=1;
	}

	if(instruction[0]=='L' && instruction[1]=='U' && instruction[2]=='I')
	{
		for(index=2;index<6;index++) opcode[index]=1;
	}
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