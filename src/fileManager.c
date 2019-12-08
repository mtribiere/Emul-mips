#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileManager.h"

/* Fonction qui calcule le nombre d'opérations dans un fichier */
int getInstructionCount(char *nameFile)
{
	FILE *fileIn;

	int nbLine=0;
	char charRead;

	fileIn=fopen(nameFile,"r");
	if(fileIn==NULL){
		 printf("Erreur lors de l'ouverture du fichier en entrée.\n\n");
		 exit(2);

	}else{
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