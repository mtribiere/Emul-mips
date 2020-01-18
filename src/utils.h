#ifndef UTILS_H 
#define UTILS_H
#include "memoryManager.h"

int getOperationSize(char *s);
void convertToBinarySized(int toConvert, char *dest,int size);
int getOperandeCount(char *s);
int getOperandeWithPosition(char *s,int index);


int charToInt(char c);
void appendStr(char *src,char *dest);
char strToHex(const char *src);
long int convertBinToInt(char *s,int size);

void initializeArray(char *s,int size);
void initializeStringArray(char *s[], int sizeArray,int sizeString);

void printMainMemory(MainMemory memory);
void printRegisters(ProcRegister registers);

#endif