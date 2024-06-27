FILES_ONE = ex_1.c
FNCTION = function.c
GCC = gcc
CFLAG = -std=c11 -Wall -Werror -Wextra
PROGRAMM = programm



ex1 :
	$(GCC) $(CFLAG) -c $(FILES_ONE) -o ex1.o
	$(GCC) $(CFLAG) -c $(FNCTION) -o function.o
	$(GCC) ex1.o function.o -o $(PROGRAMM)
	./$(PROGRAMM)

clang :
	clang-format --style=Google -n *.c
	clang-format --style=Google -i *.c

clean :
	rm -rf *.o
	rm -rf $(PROGRAMM)