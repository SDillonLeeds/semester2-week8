# Variables
CC = gcc
CFLAGS = -Wall -Wextra
TARGET = prgm
OBJS = main.o src/pgm_image.o src/pgm_display.o src/pgm_io.o src/pgm_process.o

# Default target
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
	

.PHONY: all clean

all: $(TARGET)


%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) prgm