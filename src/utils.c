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

void printer(char instruction[])
{
	int size_of_instruction=strlen(instruction);

	/* L'instruction, sans ses opérandes, est un mot de 2 à 4 lettres */ /* Peut être y en a à une lettre mais on verra */
	/* Nous allons donc déterminer la longueur de l'instruction donnée pour faire une disjonction de cas */

	if(instruction[2]==' ')
	{
		printf("\nL'instruction est composée de deux lettres.\n");
		/* Faire ici la disjonction de cas pour afficher les instructions composées de deux lettres */
	}
	else if(instruction[3]==' ')
	{
		printf("\nL'instruction est composée de trois lettres.\n");
		/* Faire ici la disjonction de cas pour afficher les instructions composées de trois lettres */
	}
	else if(instruction[4]==' ')
	{
		printf("\nL'instruction est composée de quatre lettres.\n");
		/* Faire ici la disjonction de cas pour afficher les instructions composées de quatre lettres */


		/* Premier cas : l'instruction ADDI : C EST DU PUTAIN DE BCD => lis les symboles 4 par 4*/
		/* ATTENTION ORDRE RS ET RT 	tout écrire en binaire PUIS le réécrire en BCD => deux conversions à faire */
		if(instruction[0]=='A' && instruction[1]=='D' && instruction[2]=='D' && instruction[3]=='I') printf("%x",0x200);
	}
	else printf("\nL'instruction donnée n'est pas conforme au langage MIPS.\n");
}