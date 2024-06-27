FILES_ONE = ex_1.c
FILES_TWO = ex_2.c
FILES_THEE = ex_3.c
FILES_FOUR = ex_4.c
FNCTION = function.c
GCC = gcc
CFLAG = -std=c11 -Wall -Werror -Wextra
PROGRAMM = programm



ex1 :
	$(GCC) $(CFLAG) -c $(FILES_ONE) -o ex1.o
	$(GCC) $(CFLAG) -c $(FNCTION) -o function.o
	$(GCC) ex1.o function.o -o $(PROGRAMM)
	./$(PROGRAMM)

ex2 :
	$(GCC) $(CFLAG) -c $(FILES_TWO) -o ex2.o
	$(GCC) $(CFLAG) -c $(FNCTION) -o function.o
	$(GCC) ex2.o function.o -o $(PROGRAMM)
	./$(PROGRAMM)

ex3 :
	$(GCC) $(CFLAG) -c $(FILES_THEE) -o ex3.o
	$(GCC) $(CFLAG) -c $(FNCTION) -o function.o
	$(GCC) ex3.o function.o -o $(PROGRAMM)
	./$(PROGRAMM)

ex4 :
	$(GCC) $(CFLAG) -c $(FILES_FOUR) -o ex4.o
	$(GCC) $(CFLAG) -c $(FNCTION) -o function.o
	$(GCC) ex4.o function.o -o $(PROGRAMM)
	./$(PROGRAMM)

clang :
	clang-format --style=Google -n *.c
	clang-format --style=Google -i *.c

clean :
	rm -rf *.o
	rm -rf $(PROGRAMM)