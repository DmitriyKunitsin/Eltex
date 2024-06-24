FILES_ONE = ex_1.c
FILES_TWO = ex_2.c
FUNCTION = function.c
GCC = gcc
CGFLAG = -Wall -Werror -Wextra
PROGRAMM = programm

ex1 :
	$(GCC) $(CGFLAG) -c $(FILES_ONE) -o ex1.o
	$(GCC) $(CGFLAG) -c $(FUNCTION) -o function.o
	$(GCC) ex1.o function.o -o $(PROGRAMM)
	./$(PROGRAMM)

ex2 :
	$(GCC) $(CGFLAG) -c $(FILES_TWO) -o ex2.o
	$(GCC) $(CGFLAG) -c $(FUNCTION) -o function.o
	$(GCC) ex2.o function.o -o $(PROGRAMM)
	./$(PROGRAMM)

clang_check :
	clang-format --style=Google -n $(FUNCTION)
	clang-format --style=Google -n $(FILES_ONE)
	clang-format --style=Google -n $(FILES_TWO)

clang :
	clang-format --style=Google -i $(FUNCTION)
	clang-format --style=Google -i $(FILES_ONE)
	clang-format --style=Google -i $(FILES_TWO)

clean :
	rm -rf ex1.o
	rm -rf ex2.o
	rm -rf function.o
	rm -rf $(PROGRAMM)