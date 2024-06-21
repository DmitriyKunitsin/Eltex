CFLAGS = -Wall -Werror -Wextra
CC = gcc

FUNCTION = function.c 
FILES_ONE = ex_1.c 
FILES_TWO = ex_2.c
FILES_THREE = ex_3.c
FILES_FOUR = ex_4.c
NAME_PROGRAM = programm

ex1 :
	$(CC) $(CFLAGS) -c $(FILES_ONE) -o ex_1.o
	$(CC) $(CFLAGS) -c $(FUNCTION) -o function.o
	$(CC) ex_1.o function.o -o $(NAME_PROGRAM)
	./$(NAME_PROGRAM)

ex2 :
	$(CC) $(CFLAGS) -c $(FILES_TWO) -o ex_2.o
	$(CC) $(CFLAGS) -c $(FUNCTION) -o function.o
	$(CC) ex_2.o function.o -o $(NAME_PROGRAM)
	./$(NAME_PROGRAM)

ex3 :
	$(CC) $(CFLAGS) -c $(FILES_THREE) -o ex_3.o 
	$(CC) $(CFLAGS) -c $(FUNCTION) -o function.o
	$(CC) ex_3.o function.o -o $(NAME_PROGRAM)
	./$(NAME_PROGRAM)

ex4 :
	$(CC) $(CFLAGS) -c $(FILES_FOUR) -o ex_4.o
	$(CC) $(CFLAGS) -c $(FUNCTION) -o function.o
	$(CC) ex_4.o function.o -o $(NAME_PROGRAM)
	./$(NAME_PROGRAM)

clang :
	clang-format --style=Google -n $(FILES_ONE)
	clang-format --style=Google -i $(FILES_ONE)
	clang-format --style=Google -n $(FILES_TWO)
	clang-format --style=Google -i $(FILES_TWO)
	clang-format --style=Google -n $(FILES_THREE)
	clang-format --style=Google -i $(FILES_THREE)
	clang-format --style=Google -n $(FILES_FOUR)
	clang-format --style=Google -i $(FILES_FOUR)
	clang-format --style=Google -n $(FUNCTION)
	clang-format --style=Google -i $(FUNCTION)

clean :
	rm -rf ex_1.o
	rm -rf ex_2.o 
	rm -rf ex_3.o
	rm -rf ex_4.o
	rm -rf function.o
	rm -rf $(NAME_PROGRAM)