#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileManager.h"

/* Fonction qui lit les instructions du fichier et les load*/ 
int loadInstructionfromFile(char *nameFile, char *instructions[])
{
	FILE *fileIn;
	char charRead='A';

	int lineCount=0;
	int nextCharIndex = 0;

	//Ouvrir le fichier et gerer les erreurs
	fileIn=fopen(nameFile,"r");
	if(fileIn==NULL)
	{
		printf("Erreur lors de l'ouverture du fichier en entrée.\n\n");
		exit(2);
	}
	else
	{	
		//Tant qu'on a pas atteint la fin du fichier
		while(charRead!=EOF)
		{
			//Charger le prochain caractere
			charRead=fgetc(fileIn);

			//Si c'est un retour à la ligne
			if(charRead=='\n'){
				
				//Poser la sentinelle et passer à la ligne suivante
				instructions[lineCount][nextCharIndex] = '\0';
				lineCount++;
				nextCharIndex = 0;


			}else{//Sinon

				//Charger le caractere et passer au suivant
				instructions[lineCount][nextCharIndex] = charRead;
				nextCharIndex++;

			}
		}
		
	}

	//Fermer le fichier
	fclose(fileIn);

	return lineCount;
}

/* Fonction qui écrit les instructions dans un fichier */
/* ATTENTION : l'instruction doit se terminer par \0\n */
void writeInstructionInFile(char *nameFile, char *instructions[],int instructionCount)
{
	FILE *fileOut;

	//Ouvrir le fichier et gerer les erreurs
	fileOut=fopen(nameFile,"w");
	if(fileOut==NULL)
	{
		printf("Erreur impossible de créer le fichier de sortie.\n\n");
		exit(2);
	}
	else
	{
		//Tant que toutes les instructions ne sont pas stockees
		for(int i = 0;i<instructionCount;i++){
				fputs(instructions[i],fileOut);
				fputs("\n",fileOut);
		}
		
	}

	//Fermer le fichier
	fclose(fileOut);
}