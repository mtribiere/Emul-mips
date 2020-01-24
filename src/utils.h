#ifndef UTILS_H 
#define UTILS_H
#include "memoryManager.h"
#include "Instruction/instructionInfo.h"

#define DISPLAY_PADDING 8

int getOperationSize(char *s);
void convertToBinarySized(long int toConvert, char *dest,int size);
int getOperandeCount(char *s);
int getOperandeWithPosition(char *s,int index);
char* getLabelInInstruction(char *s);
int getLineFromLabel(char *label,char *labelTable[]);

int charToInt(char c);
void appendStr(char *src,char *dest);
char strToHex(const char *src);
long int convertBinToInt(char *s,int size);

void initializeArray(char *s,int size);
void initializeStringArray(char *s[], int sizeArray,int sizeString);
void formatInstructions(char *instructions[MAX_PROGRAM_LENGTH],int instructionCount,char *labelTable[MAX_PROGRAM_LENGTH]);

void printProgramForStepMode(char *instructions[MAX_PROGRAM_LENGTH],int instructionCount ,int currentLine);
void printMainMemory(MainMemory memory);
void printRegisters(ProcRegister registers);

long int myPow(int x, int y);
long int convertBinToLongInt(int *operande);
void convertLongIntToBin(long int operande, int *toReturn);

#endif