SRC_DIR = mc/src
INC_DIR = mc/inc
PLUGINS_DIR = plugins

BUILD_DIR = build
BIN_DIR = bin

PROGRAMM_NAME = mc

GCC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
NCURSES = -lncurses

mc: lib color_plugin $(BIN_DIR)/$(PROGRAMM_NAME)

lib: build_dir
	$(GCC) $(CFLAGS) -c $(SRC_DIR)/mc.c -o $(BUILD_DIR)/mc.o 
	$(GCC) $(CFLAGS) -c $(SRC_DIR)/front.c -o $(BUILD_DIR)/front.o
	$(GCC) $(CFLAGS) -c $(SRC_DIR)/back.c -o $(BUILD_DIR)/back.o
	$(GCC) $(CFLAGS) -c $(SRC_DIR)/plugin.c -o $(BUILD_DIR)/plugin.o
	$(GCC) $(BUILD_DIR)/mc.o $(BUILD_DIR)/front.o $(BUILD_DIR)/back.o $(BUILD_DIR)/plugin.o -o $(BIN_DIR)/$(PROGRAMM_NAME) $(NCURSES)

color_plugin:
	pwd
	$(GCC) $(CFLAGS) -shared -o mc/plugins/color_plugin.so  -fPIC mc/plugins/color_plugin.c


build_dir:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)

valgrind-mc:
	valgrind --leak-check=full --show-leak-kinds=all ./bin/mc     

dvi:
	mkdir -p docs
	doxygen
	open docs/html/index.html

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(BUILD_DIR)
	rm -rf mc/plugins/color_plugin.so
	rm -rf docs