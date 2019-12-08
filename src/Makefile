all: emul-mips

emul-mips: main.o fileInstructions.o utils.o
	gcc -Wall -o $@ $^

main.o: main.c
	gcc -Wall -c $<


fileInstructions.o: fileInstructions.c
	gcc -Wall -c $<

utils.o: utils.c
	gcc -Wall -c $<

test: emul-mips
	./emul-mips
