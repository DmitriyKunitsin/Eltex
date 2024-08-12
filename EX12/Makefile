GCC = gcc
CFLAG = -std=c11 -Wall -Werror -Wextra -Wpedantic
LTR = -ltr

POSIX = task_one/POSIX/
SYSTEM_V = task_one/System_V/
BIN_DIR = task_one/bin


task1_posix: clean bin_dir
	$(GCC) $(CFLAG) $(POSIX)server.c -o $(BIN_DIR)/server_posix
	$(GCC) $(CFLAG) $(POSIX)client.c -o $(BIN_DIR)/client_posix

task1_system: clean bin_dir
	$(GCC) $(CFLAG) $(SYSTEM_V)server.c -o $(BIN_DIR)/server_sysv
	$(GCC) $(CFLAG) $(SYSTEM_V)client.c -o $(BIN_DIR)/client_sysv

bin_dir:
	mkdir -p $(BIN_DIR)

format: check
	@clang-format --style=file:.clang-format -i task_one/*/*.c

check:
	@clang-format --style=file:.clang-format -n task_one/*/*.c


clean:
	rm -rf $(BIN_DIR)