LIB_NAME = libcalc.so # Имя библиотеки
LIB_DIR = my_libs          # Директория для библиотеки
BUILD_DIR = build      # Директория для объектных файлов
SRC_DIR = src          # Директория с исходными файлами

GCC = gcc
CFLAGS = -fPIC -std=c11 -Wall -Werror -Wextra -Wpedantic
LDFLAGS = -shared

# Правило по умолчанию для сборки библиотеки
all: build_dir my_libs/libcalc.so install

install: my_libs/$(LIB_NAME)
	@mkdir -p bin
	@$(GCC) $(CFLAGS) -Wl,-rpath=$(realpath ../my_libs) src/main.c -o bin/calculate -L./my_libs -lcalc


# Правило для создания динамической библиотеки
my_libs/libcalc.so: obj
	@$(GCC) -shared -o my_libs/$(LIB_NAME) build/*.o

# Правило для компиляции исходных файлов в объектные файлы
obj: 
	@$(GCC) $(CFLAGS) -c src/add.c -o build/add.o
	@$(GCC) $(CFLAGS) -c  src/sub.c -o build/sub.o
	@$(GCC) $(CFLAGS) -c  src/mul.c -o build/mul.o
	@$(GCC) $(CFLAGS) -c  src/div.c -o build/div.o
	@$(GCC) $(CFLAGS) -c  src/helpers.c -o build/help.o

dvi: 
	mkdir -p docs
	doxygen
	open docs/html/index.html


# Правило для создания директорий
build_dir:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(LIB_DIR)

# Правило clean для удаления созданных файлов
clean:
	@rm -rf $(BUILD_DIR) $(LIB_DIR)/$(LIB_NAME) bin docs

.PHONY: all clean build_dir
