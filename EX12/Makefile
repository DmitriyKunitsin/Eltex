GCC = gcc
CFLAG = -std=c11 -Wall  -Wextra -Wpedantic
LNGCURSES = -lncurses
LPTHREAD = -lpthread

POSIX = task_one/POSIX/
SYSTEM_V = task_one/System_V/
BIN_DIR = bin
BUILD_DIR = build

SERVER_PROG = task_second/server/
CLIENT_PROG = task_second/client/
 
task1_posix: clean bin_dir
	$(GCC) $(CFLAG) $(POSIX)server.c -o $(BIN_DIR)/server_posix
	$(GCC) $(CFLAG) $(POSIX)client.c -o $(BIN_DIR)/client_posix

task1_system: clean bin_dir
	$(GCC) $(CFLAG) $(SYSTEM_V)server.c -o $(BIN_DIR)/server_sysv
	$(GCC) $(CFLAG) $(SYSTEM_V)client.c -o $(BIN_DIR)/client_sysv

all: clean bin_dir
	$(GCC) $(CFLAG) -c $(CLIENT_PROG)client.c -o $(BIN_DIR)/client_prog $(LNGCURSES)
#	$(GCC) $(CFLAG) -c $(CLIENT_PROG)front.c -o $(BUILD_DIR)/front.o
#	$(GCC) $(CFLAG) -c $(CLIENT_PROG)utils.c -o $(BUILD_DIR)/utils.o
#	ar rc $(BUILD_DIR)/client.a $(BUILD_DIR)/*.o
#	rm -rf $(BUILD_DIR)/*.o
#	$(GCC) $(CFLAG) $(CLIENT_PROG)/client.c $(BUILD_DIR)/client.a -o $(BIN_DIR)/client_prog $(LNGCURSES) $(LPTHREAD)
	$(GCC) $(CFLAG) $(SERVER_PROG)server.c -o $(BIN_DIR)/server_prog $(LPTHREAD) 

bin_dir:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)

format: check
	@clang-format --style=file:.clang-format -i task_one/*/*.c task_second/*/*.c

check:
	@clang-format --style=file:.clang-format -n task_one/*/*.c task_second/*/*.c


clean:
	rm -rf $(BIN_DIR)
	rm -rf $(BUILD_DIR)