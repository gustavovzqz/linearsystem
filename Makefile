CC = g++
CFLAGS = -Wall -Wextra -std=c++20 -pedantic
SRC_DIR = src
BIN_DIR = bin

all: $(BIN_DIR)/main

$(BIN_DIR)/main: $(SRC_DIR)/main.cpp $(SRC_DIR)/linearsystem.cpp $(SRC_DIR)/linearsystem.h
	$(CC) $(CFLAGS) $(SRC_DIR)/main.cpp $(SRC_DIR)/linearsystem.cpp -o $(BIN_DIR)/main

clean:
	rm -f $(BIN_DIR)/main

