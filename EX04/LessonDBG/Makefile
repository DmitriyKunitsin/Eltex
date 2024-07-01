Files = Pass.c
helper = help_func.c
GCC = gcc
CFLAGS = -std=c89
DOP = -fno-stack-protector -no-pie
PROGRAMM = programm

run :
	$(GCC) $(CFLAGS) $(DOP) -c -g $(Files) -o pass.o
	$(GCC) $(CFLAGS) $(DOP) -c -g $(helper) -o help.o
	$(GCC) pass.o help.o -o ./programm
	

clang :
	clang-format -style=Google -n *.c
	clang-format -style=Google -i *.c

clean :
	rm -rf *.o
	rm -rf ./programm