#ifndef UTILS_H 
#define UTILS_H

int getOperationSize(char *s);
void convertToBinarySized(int toConvert, char *dest,int size);
int getOperandeWithPosition(char *s,int index);


int charToInt(char c);
void appendStr(char *src,char *dest);
char strToHex(const char *src);

long int myPow(int x, int y);
long int binToInt(int *operande);
int* intToBin(long int operande);

#endif