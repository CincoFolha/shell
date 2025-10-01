TARGET = lsh

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
SRC = shell.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
