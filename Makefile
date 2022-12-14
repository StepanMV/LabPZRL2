.PHONY: run clean delete
main.out: main.o calc.o
	gcc main.o calc.o -o main.out -Wall -Wextra -Werror
main.o: main.c
	gcc -c main.c
calc.o: calc.c
	gcc -c calc.c
run:
	./main.out
clean:
	rm main.o calc.o
delete:
	rm main.out main.o calc.o
