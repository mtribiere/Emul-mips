#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

//*******************//
//* Champ type 0 : R 
//*			   1 : I
//*			   2 : J 
//*******************//
void operationToBinary(char *s,int type,int isSpecial,char *dest){
	
	int operande1;
	int operande2;
	int destination;

	char operationCode[7];
	char *operande1Char = NULL;
	char *operande2Char = NULL;
	char *destinationChar = NULL;

	//////////////////////////////Si c'est une operation ADDI 
	if(type == 1 && !isSpecial){

		//Creer les variables
		operande1Char = malloc(sizeof(char)*6);
		operande2Char = malloc(sizeof(char)*6);
		destinationChar = malloc(sizeof(char)*17);

		//Copier le code instruction
		strcpy(operationCode,"001000");
		
		//Recuperer les opérandes
		operande1 = getOperandeWithPosition(s,1);
		operande2 = getOperandeWithPosition(s,3);

		//Recupere la destination
		destination = getOperandeWithPosition(s,2);

		//Convertir tout en binaire
		convertToBinarySized(operande1,operande1Char,5);
		convertToBinarySized(operande2,operande2Char,16);
		convertToBinarySized(destination, destinationChar,5);
		
		//Tout stocker dans le buffer de retour
		appendStr(operationCode,dest);
		appendStr(destinationChar,dest);
		appendStr(operande1Char,dest);
		appendStr(operande2Char,dest);

	}
}