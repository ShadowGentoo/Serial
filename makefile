#set compiler
CC = gcc
#set compiler flags
CFLAGS = -Wall -O2
#set build dir
BUILD_DIR = ./build/
SOURCE_DIR = ./source/

all:
	$(CC) $(CFLAGS) -o $(BUILD_DIR)serial $(SOURCE_DIR)main.c

clean :
	rm -rf $(BUILD_DIR)*