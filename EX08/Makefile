SRC_DIR = mc/src
INC_DIR = mc/inc

BUILD_DIR = build
BIN_DIR = bin

PROGRAMM_NAME = mc

GCC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra -Wpedantic
NCURSES = -lncurses

all: lib

lib: build_dir
	$(GCC) $(CFLAGS) -c $(SRC_DIR)/mc.c -o $(BUILD_DIR)/mc.o 
	$(GCC) $(BUILD_DIR)/mc.o -o $(BIN_DIR)/$(PROGRAMM_NAME) $(NCURSES)

build_dir:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(BUILD_DIR)