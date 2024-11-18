# Makefile for testing

# Executable name
TARGET = test-make

# Compiler
CC = gcc

CFLAGS = -Wall -g

all: $(TARGET)

# Compile
$(TARGET): test-make.c
	$(CC) $(CFLAGS) -o $(TARGET) test-make.c

# Clean
clean:
	rm -f $(TARGET)
