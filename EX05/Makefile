MANAGER = contact_manager.c
FUNCTION = function.c
STRUCT = struct.c
GCC = gcc
CFLAG = -std=c11 -Wall -Werror -Wextra -Wpedantic
PROGRAM = programm
DOCS_DIR = docs

run :
	@$(GCC) $(CFLAG) -c $(MANAGER) -o manag.o
	@$(GCC) $(CFLAG) -c $(FUNCTION) -o function.o
	@$(GCC) $(CFLAG) -c $(STRUCT) -o struct.o
	@$(GCC) manag.o function.o struct.o -o $(PROGRAM)
	@./$(PROGRAM)

clang :
	clang-format --style=Google -n *.c
	clang-format --style=Google -i *.c

dvi:
	doxygen Doxyfile
	cd $(DOCS_DIR)/latex && make all

clean :
	rm -rf *.o
	rm -rf $(PROGRAM)
	rm -rf $(DOCS_DIR)