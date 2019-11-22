/**************************************/
/***Fichier pour l'instruction ADDI***/
/************************************/
#include "ADDI.h"
#include "instructionCodes.h"

/* Taille requise pour dest : 4*(taille source) + 1 */
/* A FAIRE EN GLOBAL : une fonction convertHexaToBinary 
        Prend en paramètre un nombre hexadécimal sous la forme d'un tableau 
            car ce nombre hexadécimal peut varier de 0 à 31
        Renvoie un tableau de cinq caractères ex. [11111] pour 31
*/

char convertToBinaryADDI(char *source,char *dest)
{
    char *rsBinary[6];
    char *rtBinary[6];
    char *immediateBinary[16];
 
    /* La valeur étant codée sur 16 bits, elle peut aller jusqu'à 2^16 - 1 = 65535 */
    /* Et 65535 (la valeur max) s'écrit avec cinq chiffres => taille du buffer */
    char bufferTmp[5]={0,0,0,0,0,0};

    int index;
    int offset=0;

    /* Conversion du ADDI du source dans dest */
    dest[0]=0;
    dest[1]=0;
    dest[2]=1;
    dest[3]=0;
    dest[4]=0;
    dest[5]=0;

    /* Conversion du premier argument rs du source dans dest */
    bufferTmp[5]=source[7];
    if(source[8] != ',') /* Si le nombre hexa passé en argument est composé de deux chiffres */
    {
        bufferTmp[4]=source[8];
        offset++;
    }
    rsBinary=convertHexaToBinary(bufferTmp);

    for(index=0; index<5; index++)
    {
        dest[6+index]=rsBinary[index];
    }

    /* Conversion du second argument rt du source dans dest */
    bufferTmp[5]=source[9+offset];
    if(source[10+offset] != ',') /* Si le nombre hexa passé en argument est composé de deux chiffres */
    {
        bufferTmp[4]=source[10+offset];
        offset++;
    }
    rtBinary=convertHexatoBinary(bufferTmp);

    for(index=0; index<5; index++)
    {
        dest[11+index]=rsBinary[index];
    }

    /* Conversion de la valeur immédiate passée en argument du source dans dest */
    index=0;
    while(source[11+index+offset] != '\0')
    {
        bufferTmp[5-index]=source[11+offset+index];
        index++;
    }
    for(index=0; index < 16; index++)
    {
        dest[16+index]=source[index];
    }

    return dest;
}
