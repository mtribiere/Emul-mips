/*******************************************************/
/*Fichier contenants des fonctions d'utilité (convertion, calcul de taille,....)*/
/******************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memoryManager.h"
#include "utils.h"
#include "Instruction/instructionInfo.h"

//Fonction qui calcule la taille du code opération
int getOperationSize(char *s){

	int size = 0;
	while(s[size] != ' ')
		size++;

	return size;
}

//Fonction qui converti un nombre en binaire
void convertToBinarySized(int toConvert, char *dest,int size){

	//Initialiser le tableau de retour
    int converted[size]; 
	for(int i = 0;i<size;i++)
		converted[i] = 0 ;

	//Convertir en binaire
    int i = 0; 
    while (toConvert > 0) { 
  
        converted[i] = toConvert % 2; 
        toConvert = toConvert / 2; 
        i++; 
	} 

	//Renverser la chaine
	for(int j = 0;j<size;j++){
		dest[j] = (converted[size-j-1])+48;  //Convertion en char
	}
	
}

//Obtenir le nombre d'operande
int getOperandeCount(char *s){
	int toReturn = 0;

	int i = 0;
	//Tant qu'on a pas atteint la fin de la chaine
	while(s[i] != '\0'){
		//Si on rencontre un espace ou une virgule
		if(s[i] == ' ' || s[i] == ',')
			toReturn++;

		i++;
	}

	//Ajouter le dernier opérandes
	toReturn++;
	
	return toReturn;
}

//Obtenir un operande avec une position
int getOperandeWithPosition(char *s,int index){

	int toReturn = 0;
	int currentOperandIndex = 0;

	int charIndex = 0;
	int beginIndex = 0;
	int endIndex = 0;

	//Tant qu'on atteint pas la fin de la chaine ou qu'on a pas trouvé l'index
	while(currentOperandIndex != index && s[charIndex] != '\0'){
		//Si on trouve un espace ou une virgule
		if(s[charIndex] == ' ' || s[charIndex] == ',')
			//Passer à l'operande suivant
			currentOperandIndex++;
		charIndex++;
	}

	//Tant qu'on ne trouve pas la postion du deuxième espace ou qu'on atteint la fin de la chaine
	if(s[beginIndex] == '$'){
		beginIndex = charIndex+1;
	}else{
		beginIndex = charIndex;
	}

	while(s[charIndex] != ' ' && s[charIndex] != ',' && s[charIndex] != '\0')
		charIndex++;

	//Convertir en int
	endIndex = charIndex-1;
	for(int i = beginIndex;i <= endIndex;i++){
		toReturn  = toReturn * 10 + charToInt(s[i]);
	}

	return toReturn;

}

int charToInt(char c){
	
	int toReturn = -1;
	
	switch (c)
	{
		case '1':
			toReturn = 1;	
			break;

		case '2':
			toReturn = 2;	
			break;

		case '3':
			toReturn = 3;	
			break;

		case '4':
			toReturn = 4;	
			break;

		case '5':
			toReturn = 5;	
			break;

		case '6':
			toReturn = 6;	
			break;

		case '7':
			toReturn = 7;	
			break;

		case '8':
			toReturn = 8;	
			break;

		case '9':
			toReturn = 9;	
			break;


		default:
			toReturn = 0;
			break;
	}

	return toReturn;
}

//Ajouter une chaine à la fin d'une autre
void appendStr(char *src,char *dest){
	
	//Chercher la fin de la chaine de destination
	int startIndex  = 0;
	while(dest[startIndex] != '\0')
		startIndex++;
	
	//Ajouter la chaine à la fin
	int i = 0;
	while(src[i] != '\0'){
		dest[startIndex+i] = src[i];
		i++;
	}
}

//Convertir 4 bits char en Hexa
char strToHex(const char *src){

	char toReturn;

	//Copier les 4 premiers bits
	char temp[4] = {0};
	for(int i = 0;i<4;i++)
		temp[i] = src[i];

	//Trouver le caractère à retourner
	if(strcmp(temp,"0000") == 0)
		toReturn = '0';
	else if (strcmp(temp,"0001") == 0)
		toReturn = '1'; 
  else if (strcmp(temp,"0010") == 0)
		toReturn = '2';
	else if (strcmp(temp,"0011") == 0)
		toReturn = '3';	
	else if (strcmp(temp,"0100") == 0)
		toReturn = '4';
	else if (strcmp(temp,"0101") == 0)
		toReturn = '5';
	else if (strcmp(temp,"0110") == 0)
		toReturn = '6';
	else if (strcmp(temp,"0111") == 0)
		toReturn = '7';
	else if (strcmp(temp,"1000") == 0)
		toReturn = '8';
	else if (strcmp(temp,"1001") == 0)
		toReturn = '9';
	else if (strcmp(temp,"1010") == 0)
		toReturn = 'A';
	else if (strcmp(temp,"1011") == 0)
		toReturn = 'B';
	else if (strcmp(temp,"1100") == 0)
		toReturn = 'C';
	else if (strcmp(temp,"1101") == 0)
		toReturn = 'D';
	else if (strcmp(temp,"1110") == 0)
		toReturn = 'E';
	else if (strcmp(temp,"1111") == 0)
		toReturn = 'F';

	return toReturn;
}

long int convertBinToInt(char *s,int size){
	
	long int toReturn = 0;
	int currentMul = 1;
	//Pour tous les bits
	for(int i = size-1;i>=0;i--){
		
		//Si le bit est à 1
		if(s[i] == '1'){
			toReturn += currentMul;
		}

		//Passer au bit suivant
		currentMul *= 2;
	}

	return toReturn;
}

void initializeArray(char *s,int size){
	for(int i = 0;i<size;i++)
		s[i] = 0;
}

void initializeStringArray(char *s[], int sizeArray,int sizeString){
	for(int i = 0;i<sizeArray;i++){
		s[i] = malloc(sizeof(char)*sizeString);
		initializeArray(s[i],sizeString);
	}
}

void formatInstructions(char *instructions[MAX_PROGRAM_LENGTH],int instructionCount,char *labelTable[MAX_PROGRAM_LENGTH]){
	
	//Parcourir toutes les instructions
	for(int i = 0;i<instructionCount;i++){

		//////Parcourir la ligne
		for(int index = 0;instructions[i][index] != '\0';index++){

			////////Si on rencontre un caractère de label
			if(instructions[i][index] == ':'){
				
				//Copier le nom du label dans la table
				int tempIndex = 0;
				while(tempIndex < index){
					labelTable[i][tempIndex] = instructions[i][tempIndex];
					tempIndex++;
				}
				
				//Déplacer l'instruction
				tempIndex = 0;
				index++;
				while(instructions[i][index] != '\0'){

					instructions[i][tempIndex] = instructions[i][index];
					tempIndex++;
					index++;

				}

				instructions[i][tempIndex] = '\0';
				index = 0;
			}

			
			/////////Si on rencontre un caratère de commentaire
			if(instructions[i][index] == '#'){
				
				////Supprimer le commentaire 
				if(instructions[i][index-1] == ' '){
					instructions[i][index-1] = '\0';	
				}else{
					instructions[i][index] = '\0';
				}

			}


		}

	}
}


void printMainMemory(MainMemory memory){

	//Pour tout les index
	for(int i = 0;i<(memory.memorySize);i++){
		if(i%8 == 0){
			printf("\n %d   : ",i);
		}
		printf(" %x ",(memory.mem)[i]);
	}

	printf("\n");

}

void printRegisters(ProcRegister registers){

	//Pour tout les index
	for(int i = 0;i<(registers.memorySize);i++){
		printf("%d : %ld       ",i,loadFromRegister(i,registers));

		if((i-2)%3 == 0) printf("\n");
	}
	printf("\n\n");
}
