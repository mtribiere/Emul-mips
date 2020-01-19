EXE = emul-mips
CC=gcc

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c)\
	  $(wildcard $(SRC_DIR)/Instruction/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS += -Iinclude -I$(SRC_DIR)
CFLAGS += -Wall -g 
LDFLAGS += -Llib
LDLIBS += -lm

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

test: $(EXE)
	./$(EXE) testFiles/in3.txt test

check: $(EXE)
	mkdir tests
	cp testFiles/in3.txt tests
	mkdir hexified 
	echo '\n' | exemple/exemples2019/emul-mips in3.txt 
	./$(EXE) exemple/exemples2019/tests/in3.txt hexified/in3-2.txt
	diff -i hexified/in3.txt hexified/in3-2.txt
	

