#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#define REGISTER_COUNT 50
#define MAIN_MEMORY_SIZE 100

typedef struct procRegister
{
    int memorySize;
    int *mem;

}ProcRegister;

typedef struct mainMemory
{
	int memorySize;
	int *mem; 
} MainMemory;

void initializeRegister(int size,ProcRegister *registers);
void initializeMemory(int size, MainMemory *memory);

int loadFromRegister(int index, ProcRegister registers);
void storeInRegister(int toStore, int index, ProcRegister *registers);


int loadFromMemory(int index, MainMemory *memory);
void storeInMemory(int toStore, int index, MainMemory *memory);

void freeRegisters(ProcRegister *registers);
void freeMainMemory(MainMemory *memory);

void checkRegisterIndex(int index);


#endif