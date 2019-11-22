all: emul-mips

emul-mips: main.o utils.o
	gcc -Wall -o $@ $^

main.o: main.c
	gcc -Wall -c $<


utils.o: utils.c
	gcc -Wall -c $<

test: emul-mips
	./emul-mips