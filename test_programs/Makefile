
CC = clang
CFLAGS = -Wall -Werror -gdwarf-4

SRC_DIR = src
BIN_DIR = bin

SRCS := $(wildcard $(SRC_DIR)/**/*.c)
BINS := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(SRCS))

.PHONY: all clean

all: $(BIN_DIR) $(BINS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
	mkdir -p $(dir $(BINS))

$(BIN_DIR)/%: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR)/*
	rmdir $(BIN_DIR)

