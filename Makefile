TARGET := lsh

# Toolchain (overrideable)
CC ?= gcc
CFLAGS ?= -Wall -Wextra -Werror -pedantic -g
LDFLAGS ?=
STRIP ?= strip

# Installation
PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
DESTDIR ?=

# Sources (auto-detect) and objects/deps
SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
DEPS := $(OBJ:.o=.d)

# Verbose toggle: `make V=1` to show commands
ifeq ($(V),1)
  Q =
else
  Q = @
endif

.PHONY: all clean rebuild install uninstall run help

all: $(TARGET)

$(TARGET): $(OBJ)
	$(Q)$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	$(Q)if [ -n "$(STRIP)" ]; then $(STRIP) $@ || true; fi

-include $(DEPS)

%.o: %.c
	$(Q)$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

run: all
	$(Q)./$(TARGET)

install: all
	$(Q)install -d $(DESTDIR)$(BINDIR)
	$(Q)install -m 0755 $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)

uninstall:
	$(Q)rm -f $(DESTDIR)$(BINDIR)/$(TARGET)

clean:
	$(Q)rm -f $(TARGET) $(OBJ) $(DEPS)

rebuild: clean all

help:
	@echo "Available targets:"
	@echo "  make all            - Build the shell (default)"
	@echo "  make clean          - Remove build artifacts"
	@echo "  make rebuild        - Clean and build"
	@echo "  make run            - Build and run the shell"
	@echo "  make install        - Install to \$(PREFIX)/bin (use DESTDIR=... for packaging)"
	@echo "  make uninstall      - Remove from \$(PREFIX)/bin"
	@echo ""
	@echo "Environment overrides:"
	@echo "  CC, CFLAGS, LDFLAGS, PREFIX, BINDIR, DESTDIR, STRIP"
	@echo "Examples:"
	@echo "  make                # build"
	@echo "  make V=1            # show commands"
	@echo "  make install PREFIX=/opt/myapp"
