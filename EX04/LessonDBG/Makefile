Files = Pass.c
helper = help_func.c
GCC = gcc
CFLAGS = -std=c89
DOP = -fno-stack-protector -no-pie
PROGRAMM = programm

run :
	@$(GCC) $(CFLAGS) $(DOP) -c -g $(Files) -o pass.o
	@$(GCC) $(CFLAGS) $(DOP) -c -g $(helper) -o help.o
	@$(GCC) pass.o help.o -o ./programm
	@echo "\033[36mПроект успешно собран, для запуска введите ./programm\033[0m"

clang :
	@clang-format -style=Google -n *.c
	@clang-format -style=Google -i *.c
	@echo "\033[36mПроверка стиля прошла успешно\033[0m"

clean :
	@rm -rf *.o
	@rm -rf ./programm
	@echo  "\033[36mПроект успешно удален\033[0m"