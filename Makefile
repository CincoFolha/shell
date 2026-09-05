SHELL := /usr/bin/env sh
.DEFAULT_GOAL := all

TARGET := lsh

# Toolchain (overrideable)
CC ?= gcc
CPPFLAGS ?=
CFLAGS ?= -Wall -Wextra -Werror -pedantic -g -O2
LDFLAGS ?=
LDLIBS ?=
STRIP ?= strip

# Installation
PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
DESTDIR ?=

# Helpers (overrideable)
RM ?= rm -f
RM_RF ?= rm -rf
MKDIR_P ?= mkdir -p

# Sources (auto-detect) and objects/deps (out-of-source)
SRC := $(wildcard *.c)
OBJDIR ?= build
OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))
DEPS := $(OBJ:.o=.d)

# Verbose toggle: `make V=1` to show commands
ifeq ($(V),1)
  Q =
else
  Q = @
endif

.PHONY: all clean distclean rebuild install uninstall run help

all: $(TARGET)

$(TARGET): $(OBJ)
	$(Q)$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	$(Q)if command -v $(STRIP) >/dev/null 2>&1 && [ -n "$(STRIP)" ]; then $(STRIP) $@ || true; fi

-include $(DEPS)

# Build object files in $(OBJDIR) from sources in the source tree.
# The -MF ensures .d files go next to their .o files inside OBJDIR.
$(OBJDIR)/%.o: %.c
	$(Q)$(MKDIR_P) $(dir $@)
	$(Q)$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(@:.o=.d) -c $< -o $@

run: all
	$(Q)./$(TARGET)

install: all
	$(Q)$(MKDIR_P) $(DESTDIR)$(BINDIR)
	$(Q)install -m 0755 $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)

uninstall:
	$(Q)$(RM) $(DESTDIR)$(BINDIR)/$(TARGET)

clean:
	$(Q)$(RM) $(TARGET) $(OBJ) $(DEPS)

# remove generated build directory (careful: will remove whole OBJDIR)
distclean: clean
	$(Q)$(RM_RF) $(OBJDIR)

rebuild: clean all

help:
	@echo "Available targets:"
	@echo "  make all            - Build the shell (default)"
	@echo "  make clean          - Remove build artifacts (keeps OBJDIR)"
	@echo "  make distclean      - Remove build artifacts and OBJDIR"
	@echo "  make rebuild        - Clean and build"
	@echo "  make run            - Build and run the shell"
	@echo "  make install        - Install to \$(PREFIX)/bin (use DESTDIR=... for packaging)"
	@echo "  make uninstall      - Remove from \$(PREFIX)/bin"
	@echo ""
	@echo "Environment overrides:"
	@echo "  CC, CPPFLAGS, CFLAGS, LDFLAGS, LDLIBS, PREFIX, BINDIR, DESTDIR, STRIP, OBJDIR"
	@echo "Examples:"
	@echo "  make                 # build, objects go into ./build/"
	@echo "  make V=1             # show commands"
	@echo "  make OBJDIR=out/debug# out-of-source build into out/debug/"
	@echo "  make distclean       # remove generated build directory"
