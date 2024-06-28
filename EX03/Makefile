MANAGER = contact_manager.c
FUNCTION = function.c
GCC = gcc
CFLAG = -std=c11 -Wall -Werror -Wextra
PROGRAM = programm

run :
	@$(GCC) $(CFLAG) -c $(MANAGER) -o manag.o
	@$(GCC) $(CFLAG) -c $(FUNCTION) -o function.o
	@$(GCC) manag.o function.o -o $(PROGRAM)
	@./$(PROGRAM)

clang :
	clang-format --style=Google -n *.c
	clang-format --style=Google -i *.c

clean :
	rm -rf *.o
	rm -rf $(PROGRAM)