
CC := gcc
CFLAGS := -O2 -g -Wall -Wextra
LIBS := -lm

.PHONY: all clean

all: main

main: main.c
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	$(RM) main

