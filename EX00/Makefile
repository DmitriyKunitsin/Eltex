CFLAGS = -Wall -Werror -Wextra
CC = gcc

FUNCTION = function.c 
FILES_ONE = ex_1.c 
FILES_TWO = ex_2.c
FILES_THREE = ex_3.c

ex1 :
	$(CC) $(CFLAGS) -c $(FILES_ONE) -o ex_1.o
	$(CC) $(CFLAGS) -c $(FUNCTION) -o function.o
	$(CC) ex_1.o function.o -o programm
	./programm

ex2 :
	$(CC) $(CFLAGS) -c $(FILES_TWO) -o ex_2.o
	$(CC) $(CFLAGS) -c $(FUNCTION) -o function.o
	$(CC) ex_2.o function.o -o programm
	./programm

ex3 :
	$(CC) $(CFLAGS) -c $(FILES_THREE) -o ex_3.o 
	$(CC) $(CFLAGS) -c $(FUNCTION) -o function.o
	$(CC) ex_3.o function.o -o programm
	./programm


clang :
	clang-format --style=Google -n $(FILES_ONE)
	clang-format --style=Google -i $(FILES_ONE)
	clang-format --style=Google -n $(FILES_TWO)
	clang-format --style=Google -i $(FILES_TWO)
	clang-format --style=Google -n $(FUNCTION)
	clang-format --style=Google -i $(FUNCTION)

clean :
	rm -rf ex_1.o
	rm -rf ex_2.o 
	rm -rf ex_3.o
	rm -rf function.o
	rm -rf programm