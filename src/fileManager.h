#ifndef FILEMANAGER_H 
#define FILEMANAGER_H

int getOperationSize(char *s);

int getInstructionCount(char *string);

int loadInstructionfromFile(char *nameFile, char *instructions[]);

void writeInstructionInFile(char *nameFile, char *instructions[],int instructionCount);

#endif