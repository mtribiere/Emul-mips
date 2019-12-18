#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Instruction/instructionConverter.h"
#include "Instruction/instructionInfo.h"
#include "utils.h"


//Convertir les instructions en hexa
void instructionToHex(char *s,char *dest)
{

	///////////////Ignorer les commentaires
	
	int index = 0;
	//Parcourir l'instruction
	while(s[index] != '\0'){

		//Si on trouve un symbole de commentaire
		if(s[index] == '#'){

			//Trouver l'endroit où inserer la sentinelle
			if(s[index-1] == ' ') 
				s[index-1] = '\0';
			else
				s[index] = '\0';		
					
		}

		index++; 
	}

	///////////////Obtenir le binaire de l'instruction
	char instructionBinary[33]={0};
	instructionBinary[32] = '\0';

	instructionToBinary(s,getInstructionType(s),getIsSpecial(s),instructionBinary);

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


	//////////////////////////////Si c'est une operation de type R
	if(type == 0){

		//Creer les varibales
		operande1Char = malloc(sizeof(char)*6);
		operande2Char = malloc(sizeof(char)*6);
		destinationChar = malloc(sizeof(char)*6);

		initializeArray(operande1Char,6);		
		initializeArray(operande2Char,6);		
		initializeArray(destinationChar,6);

		//Copier le code operation
		getOperationCode(s,operationCode);

		//Recuperer les operandes
		operande1 = getOperandeWithPosition(s,2);
		operande2 = getOperandeWithPosition(s,3);
		destination = getOperandeWithPosition(s,1);

		//Convertir les operandes en binaire
		convertToBinarySized(operande1,operande1Char,5);
		convertToBinarySized(operande2,operande2Char,5);
		convertToBinarySized(destination,destinationChar,5);

		/////Si c'est un type special
		if(isSpecial){
			
			//Ajouter l'opcode à la fin et du padding au debut
			appendStr("000000",dest);
			appendStr(operande1Char,dest);
			appendStr(operande2Char,dest);
			appendStr(destinationChar,dest);
			appendStr("00000",dest);
			appendStr(operationCode,dest);
		
		}else{

			//Ajouter l'opcode au debut et du padding à la fin
			appendStr(operationCode,dest);
			appendStr(operande1Char,dest);
			appendStr(operande2Char,dest);
			appendStr(destinationChar,dest);
			appendStr("00000",dest); //Registre SA 
			appendStr("000000",dest); //Padding
		
		}

		//Liberer la memoire
		free(operande1Char);
		free(operande2Char);
		free(destinationChar);
	}

	//////////////////////////////Si c'est une operation de type I et qu'elle est non special
	if(type == 1 && !isSpecial){

		//Creer les variables
		operande1Char = malloc(sizeof(char)*6);
		operande2Char = malloc(sizeof(char)*17);
		destinationChar = malloc(sizeof(char)*6);

		initializeArray(operande1Char,6);		
		initializeArray(operande2Char,17);		
		initializeArray(destinationChar,6);

		//Copier le code instruction
		getOperationCode(s,operationCode);
		
		//Recuperer les opérandes
		operande1 = getOperandeWithPosition(s,1);
		operande2 = getOperandeWithPosition(s,3);

		//Recupere la destination
		destination = getOperandeWithPosition(s,2);

		//Convertir tout en binaire
		convertToBinarySized(operande1,operande1Char,5);
		convertToBinarySized(operande2,operande2Char,16);
		convertToBinarySized(destination, destinationChar,5);

		operande1Char[5] = '\0';
		operande2Char[16] = '\0';
		destinationChar[5] = '\0';
		
		
		//Tout stocker dans le buffer de retour
		appendStr(operationCode,dest);
		appendStr(destinationChar,dest);
		appendStr(operande1Char,dest);
		appendStr(operande2Char,dest);

		//Liberer la memoire
		free(operande1Char);
		free(operande2Char);
		free(destinationChar);
	}
}