#ifndef MEMORY_INSTRUCTIONS_H
#define MEMORY_INSTRUCTIONS_H

#define REGISTER_SIZE 50
#define MEMORY_SIZE 100

/* ATTENTION le mot register est un mot réservé par le langage!!!!! */
typedef struct registre registre;
struct registre
{
    int nbInstructionsInside;
    char instructions[REGISTER_SIZE][32];
};

typedef struct memory memory;
struct memory
{
    int nbInstructionsInside;
    char instructions[MEMORY_SIZE][32];
};

void initializeRegister(registre *myRegister);

void initializeMemory(memory *myMemory);

void loadIntoRegister(char *instruction, registre *myRegister);

void loadIntoMemory(char *instruction, memory *myMemory);

void storeIntoRegister(char *instruction, int indexInstruction, registre *myRegister);


#endif