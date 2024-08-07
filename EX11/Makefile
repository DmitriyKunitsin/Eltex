
GCC = gcc

CFLAG = -std=c11  -Wall -Werror -Wextra

RESULT = result
CLIENT_DIR = client
CLIENT = client_exe
SERVER_DIR = server
SERVER = server_exe

ex1: clean
	$(GCC) $(CFLAG) ex1.c -o $(RESULT)
	./$(RESULT)

ex2: clean
	mkdir -p $(SERVER_DIR)
	mkdir -p $(CLIENT_DIR)
	$(GCC) $(CFLAG) $(SERVER_DIR)/server.c -o $(SERVER_DIR)/$(SERVER)
	$(GCC) $(CFLAG) $(CLIENT_DIR)/client.c -o $(CLIENT_DIR)/$(CLIENT)

ex3: clean
	$(GCC) $(CFLAG) ex3.c -o $(RESULT)
	@echo "\033[35m] Для теста интопретатора введите\n ( ls  -la test_directory | grep d ), создал тестовую директорию\033[0m"
	@./$(RESULT)

clean:
	@echo "\033[31m] Извините, что мало декомпозиции, просто я заболел и сил совсем нет :(  \033[0m"
	@rm -rf $(RESULT)
	@rm -rf $(SERVER_DIR)/$(SERVER)
	@rm -rf $(CLIENT_DIR)/$(CLIENT)
	@rm -rf $(SERVER_DIR)/my_fifo