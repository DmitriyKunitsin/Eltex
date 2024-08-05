GCC = gcc
CFLAG = -std=c11 -Wall -Werror -Wextra 
PTHREAD = -lpthread

EX1 = ex1.c
EX2 = ex2.c

MARKET_DIR = market
BUILD_DIR = build
BIN_DIR = bin

PROGRAM_NAME = result

ex1: clean
	$(GCC) $(CFLAG) $(EX1) -o $(PROGRAM_NAME)

ex2: clean
	$(GCC) $(CFLAG) $(EX2) -o $(PROGRAM_NAME)

market: market.a
	$(GCC) $(CFLAG) $(MARKET_DIR)/main.c $(MARKET_DIR)/$(BUILD_DIR)/market.a -o $(MARKET_DIR)/$(BIN_DIR)/market $(PTHREAD)
	$(MARKET_DIR)/$(BIN_DIR)/./market

market.a: build_dir
	$(GCC) $(CFLAG) -c $(MARKET_DIR)/market.c -o $(MARKET_DIR)/$(BUILD_DIR)/market.o
	ar rc $(MARKET_DIR)/$(BUILD_DIR)/market.a $(MARKET_DIR)/$(BUILD_DIR)/market.o 
	rm -rf $(MARKET_DIR)/$(BUILD_DIR)/market.o

build_dir:
	mkdir -p $(MARKET_DIR)/$(BUILD_DIR)
	mkdir -p $(MARKET_DIR)/$(BIN_DIR)

clean:
	rm -rf $(PROGRAM_NAME)
	rm -rf $(MARKET_DIR)/$(BUILD_DIR)
	rm -rf $(MARKET_DIR)/$(BIN_DIR)