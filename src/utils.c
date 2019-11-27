/*******************************************************/
/*Fichier contenants des fonctions d'utilité (convertion, calcul de taille,....)*/
/******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/* Fonction qui calcule la taille du code opération */
int getOperationSize(char *s){

	int size = 0;
	while(s[size] != ' ')
		size++;

	return size;
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
			printf("\nDébut de la boucle \n\n");
			if(charRead=='\n') nbLine++;
			charRead=fgetc(fileIn);
			printf(" nbLine : %d	charRead : %c char attendu : %c \n\n",nbLine,charRead,'\\');
			printf("\nFin de la boucle \n\n");
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

	fileIn=fopen(nameFile,"r+");
	if(fileIn==NULL)
	{
		printf("Erreur lors de l'ouverture du fichier en entrée.\n\n");
		instruction=NULL;
	}
	else
	{
		charRead=fgetc(fileIn);
		printf("Entrée dans la boucle ok \n\n");

		while(charRead!=EOF && nbLine!=id)
		{
			if(charRead=='\n') nbLine++;
			if(nbLine!=id) charRead=fgetc(fileIn);
			//printf(" nbLine : %d	charRead : %c \n\n",nbLine,charRead);
		}

		if(nbLine==id)
		{
			printf("Destination atteinte !! \n\n");
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