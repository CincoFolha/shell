TARGET := lsh
CC := gcc

CFLAGS := -Wall -Wextra -Werror -pedantic -g

SRC := shell.c
OBJ := $(SRC:.c=.o)

.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)

rebuild: clean all
