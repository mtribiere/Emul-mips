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

/* A FAIRE EN GLOBAL : une fonction convertHexaToBinary 
        Prend en paramètre un nombre hexadécimal sous la forme d'un tableau de max 
        Renvoie un tableau de cinq caractères ex. [11111] pour 31
*/
char *convertHexaToBinary()
