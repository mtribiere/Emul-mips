#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

//Le dernier registre est le PC
#define SPECIAL_REGISTERS_COUNT 3
#define REGISTER_COUNT 15+SPECIAL_REGISTERS_COUNT
#define PC_REGISTER REGISTER_COUNT-1
#define MAIN_MEMORY_SIZE 4*40

typedef struct procRegister
{
    int memorySize;
    long int *mem;

}ProcRegister;

typedef struct mainMemory
{
	int memorySize;
	int *mem; 
} MainMemory;

void initializeRegister(int size,ProcRegister *registers);
void initializeMemory(int size, MainMemory *memory);

long int loadFromRegister(int index, ProcRegister registers);
void storeInRegister(long int toStore, int index, ProcRegister *registers);


long int loadFromMemory(int index, MainMemory memory);
void storeInMemory(long int toStore, long int index, MainMemory *memory);

void freeRegisters(ProcRegister *registers);
void freeMainMemory(MainMemory *memory);

void checkRegisterIndex(int index);
void checkMemoryAddress(int index);


#endif