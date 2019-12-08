#ifndef FILEMANAGER_H 
#define FILEMANAGER_H

int getOperationSize(char *s);

int getInstructionCount(char *string);

void readInstructionInFile(char *nameFile, int id, char *instruction);

void writeInstructionInFile(char *nameFile, int id, char *instruction);


#endif