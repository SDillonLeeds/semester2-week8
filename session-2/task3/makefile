# Variables
CC = gcc
CFLAGS = -Wall -Wextra
TARGET = student
OBJS = main.o student.o

# Default target
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o prgm
	

.PHONY: all clean

all: $(TARGET)


%.o: %.c student.h structure.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) prgm