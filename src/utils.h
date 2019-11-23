#ifndef UTILS_H 
#define UTILS_H

int getOperationSize(char *s);
void convertToBinarySized(const char *s, char *dest,int size);
char *convertInstructionToBinary(char *s, int isSpecial,int instructionCode);

#endif