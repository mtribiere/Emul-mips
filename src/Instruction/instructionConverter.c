#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Instruction/instructionConverter.h"
#include "utils.h"


//Convertir les instructions en hexa
void instructionToHex(char *s,char *dest){

	///////////////Obtenir le binaire de l'instruction
	char instructionBinary[33]={0};
	instructionBinary[32] = '\0';

	
	//Si l'instruction est de type I
	if(strstr(s,"ADDI") != NULL){
			instructionToBinary(s,1,0,instructionBinary);
	}

	//////////////Convertir en hexa
	int destinationIndex = 0;
	for(int i = 0;i<32;i+=4){
		char temp = strToHex(instructionBinary+i);
		dest[destinationIndex] = temp;
		destinationIndex++;
	}

}

//*******************//
//* Champ type 0 : R 
//*			   1 : I
//*			   2 : J 
//*******************//
void instructionToBinary(char *s,int type,int isSpecial,char *dest){
	
	int operande1;
	int operande2;
	int destination;

	char operationCode[7];
	char *operande1Char = NULL;
	char *operande2Char = NULL;
	char *destinationChar = NULL;

	//////////////////////////////Si c'est une operation de type I et qu'elle est non special
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