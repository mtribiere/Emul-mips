#ifndef UTILS_H 
#define UTILS_H

int getOperationSize(char *s);

int getInstructionCount(char *string);

void readInstructionInFile(char *nameFile, int id, char *instruction);

void writeInstructionInFile(char *nameFile, int id, char *instruction);

//char *convertHexaToBinary(char *string);

#endif