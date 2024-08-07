
GCC = gcc

CFLAG = -std=c11  -Wall -Werror -Wextra

RESULT = result


ex1: clean
	$(GCC) $(CFLAG) ex1.c -o $(RESULT)
	./$(RESULT)

clean:
	rm -rf $(RESULT)