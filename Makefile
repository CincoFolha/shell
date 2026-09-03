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

help:
	@echo "Available targets:"
	@echo "  make all       - Build the shell"
	@echo "  make clean     - Remove build artifacts"
	@echo "  make rebuild   - Clean and build"
	@echo "  make run       - Build and run the shell"
	@echo "  make install   - Install to /usr/local/bin"
	@echo "  make uninstall - Remove from /usr/local/bin"
