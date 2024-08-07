
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

clean:
	rm -rf $(RESULT)
	rm -rf $(SERVER_DIR)/$(SERVER)
	rm -rf $(CLIENT_DIR)/$(CLIENT)
	rm -rf $(SERVER_DIR)/my_fifo