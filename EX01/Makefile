FILES_ONE = ex_1.c
FILES_TWO = ex_2.c
FILES_THREE = ex_3.c
FILES_FOUR = ex_4.c
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

ex3 :
	$(GCC) $(CGFLAG) -c $(FILES_THREE) -o ex3.o
	$(GCC) $(CGFLAG) -c $(FUNCTION) -o function.o
	$(GCC) ex3.o function.o -o $(PROGRAMM)
	./$(PROGRAMM)

ex4 :
	$(GCC) $(CGFLAG) -c $(FILES_FOUR) -o ex4.o
	$(GCC) $(CGFLAG) -c $(FUNCTION) -o function.o
	$(GCC) ex4.o function.o -o $(PROGRAMM)
	./$(PROGRAMM)

CFcheck :
	clang-format --style=Google -n *.c

clang :
	clang-format --style=Google -i *.c

clean :
	rm -rf *.o
	rm -rf $(PROGRAMM)