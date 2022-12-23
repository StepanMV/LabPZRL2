.PHONY: run clean delete
main.out: main.o calc.o toNum.o toStr.o
	gcc main.o calc.o toNum.o toStr.o -o main.out -Wall -Wextra -Werror
main.o: main.c
	gcc -c main.c
calc.o: calc.c
	gcc -c calc.c
toNum.o: toNum.c
	gcc -c toNum.c
toStr.o: toStr.c
	gcc -c toStr.c
run:
	./main.out
clean:
	rm main.o calc.o toNum.o toStr.o
delete:
	rm main.out main.o calc.o toNum.o toStr.o
