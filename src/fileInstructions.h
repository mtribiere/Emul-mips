#ifndef FILEINSTRUCTIONS_H 
#define FILEINSTRUCTION_H

int getOperationSize(char *s);

int getInstructionCount(char *string);

void getOperationCode(char *instruction, char *opcode);

void readInstructionInFile(char *nameFile, int id, char *instruction);

void writeInstructionInFile(char *nameFile, int id, char *instruction);

//char *convertHexaToBinary(char *string);

#endif