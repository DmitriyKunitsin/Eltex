LIB_NAME = libcalc
LIB_DIR = lib
BUILD_DIR = build
BIN_DIR = bin
SRC = src


GCC = gcc
CFLAG = -std=c11 -Wall -Werror -Wextra -Wpedantic

all: install

install: libcalc.a
	@mkdir -p $(BIN_DIR)
	$(GCC) $(CFLAG) main.c $(LIB_DIR)/$(LIB_NAME).a -o $(BIN_DIR)/calculate 

libcalc.a: build_dir
	$(GCC) $(CFLAG) -c $(SRC)/add.c -o $(BUILD_DIR)/add.o
	$(GCC) $(CFLAG) -c $(SRC)/sub.c -o $(BUILD_DIR)/sub.o
	$(GCC) $(CFLAG) -c $(SRC)/mul.c -o $(BUILD_DIR)/mul.o
	$(GCC) $(CFLAG) -c $(SRC)/div.c -o $(BUILD_DIR)/div.o
	$(GCC) $(CFLAG) -c $(SRC)/helpers.c -o $(BUILD_DIR)/help.o
	ar rc $(LIB_DIR)/$(LIB_NAME).a $(BUILD_DIR)/*.o
	ranlib $(LIB_DIR)/$(LIB_NAME).a
	rm -rf $(BUILD_DIR)/*.o



build_dir:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(LIB_DIR)

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(LIB_DIR)
	@rm -rf $(BIN_DIR)