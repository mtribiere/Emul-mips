#ifndef INSTRUCTION_INFO
#define INSTRUCTION_INFO

#define MAX_PROGRAM_LENGTH 50
#define MAX_INSTRUCTION_LENGTH 50
#define INSTRUCTION_HEX_LENGTH 9
#define MAX_LABEL_NAME_LENGTH 40

int getInstructionType(const char *s);
int getIsSpecial(const char *instruction);
void getOperationCode(char *instruction, char *opcode);

#endif