
GCC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic

EX1 = ex1.c
EX2 = ex2.c
EX3 = ex3.c


RESULT_PROGRAM = result

ex1: clean
	$(GCC) $(CFLAGS) $(EX1) -o $(RESULT_PROGRAM)

ex2: clean
	$(GCC) $(CFLAGS) $(EX2) -o $(RESULT_PROGRAM)

ex3: clean
	$(GCC) $(CFLAGS) $(EX3) -o $(RESULT_PROGRAM)


clean:
	rm -rf $(RESULT_PROGRAM)