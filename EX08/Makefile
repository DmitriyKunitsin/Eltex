SRC_DIR = mc/src
INC_DIR = mc/inc
PLUGINS_DIR = plugins

BUILD_DIR = build
BIN_DIR = bin

PROGRAMM_NAME = mc

GCC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
NCURSES = -lncurses

debug: install color_plugin
	$(GCC) $(CFLAGS) $(SRC_DIR)/mc.c $(BUILD_DIR)/mc.a -g -o $(BIN_DIR)/mc -lncurses


mc: install color_plugin
	$(BIN_DIR)/$(PROGRAMM_NAME)

install : lib
	$(GCC) $(CFLAGS) $(SRC_DIR)/mc.c $(BUILD_DIR)/mc.a -o $(BIN_DIR)/mc -lncurses


lib: build_dir
	$(GCC) $(CFLAGS) -c $(SRC_DIR)/front.c -o $(BUILD_DIR)/front.o
	$(GCC) $(CFLAGS) -c $(SRC_DIR)/back.c -o $(BUILD_DIR)/back.o
	$(GCC) $(CFLAGS) -c $(SRC_DIR)/plugin.c -o $(BUILD_DIR)/plugin.o
	ar rc $(BUILD_DIR)/mc.a $(BUILD_DIR)/*.o
	rm -rf $(BUILD_DIR)/*.o

color_plugin:
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

format : check
	clang-format --style=file:.clang-format -i mc/src/*.c mc/*/*.c

check :
	@clang-format --style=file:.clang-format -n mc/src/*.c mc/*/*.c


clean:
	rm -rf $(BIN_DIR)
	rm -rf $(BUILD_DIR)
	rm -rf mc/plugins/color_plugin.so
	rm -rf docs