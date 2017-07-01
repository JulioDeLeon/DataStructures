OUTPUT_DIR= ./build
INCLUDE_DIR= ./include
LIB_DIR= ./lib
SRC_DIR= ./src
CC=gcc
CFLAGS= -g -Wall
INCLUDES= -I$(INCLUDE_DIR)
LIBRARIES= -L$(LIB_DIR)
TARGET=treasure

binary_tree: $(SRC_DIR)/binary_tree.c
	$(CC) $(CFLAGS) $(INCLUDES) -fPIC -shared -o $(LIB_DIR)/$@.so $^

$(TARGET): $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBARIES) -o $(OUTPUT_DIR)/$(TARGET) $^

all: binary_tree $(TARGET)

clean:
	rm -rf $(OUTPUT_DIR)/*

purge:
	rm -rf $(OUTPUT_DIR)/* $(LIB_DIR)/*
