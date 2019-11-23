/*******************************************************/
/*Fichier contenants des fonctions d'utilité (convertion, calcul de taille,....)*/
/******************************************************/

#include <stdlib.h>
#include "utils.h"

//Fonction qui calcule la taille du code opération
int getOperationSize(char *s){

	int size = 0;
	while(s[size] != ' ')
		size++;

	return size;
}

//Fonction qui converti un nombre en binaire
void convertToBinarySized(const char *s, char *dest,int size){
	
	//Convertir en int le nombre
	int toConvert = atoi(s);

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

	/*
	//DEBUG
	for(int j = 0;j<size;j++)
		printf(" %d ",converted[j]);

	printf("\n");
	*/

	//Renverser la chaine
	for(int j = 0;j<size;j++){
		dest[j] = (converted[size-j-1])+48;  //Convertion en char
		//printf(" %d ",dest[j]);
	}
	
}

//Fonction qui converti une instruction en binaire
char *convertInstructionToBinary(char *s, int isSpecial,int instructionCode){

	//Convertir le code opération en binaire
	


}