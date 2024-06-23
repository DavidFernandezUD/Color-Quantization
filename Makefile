
CC := gcc
CFLAGS := -O2 -g -Wall -Wextra
HEADERS := include/
LIBS := -lm

.PHONY: all clean

all: main

main: main.c kmeans.c
	$(CC) $(CFLAGS) -I $(HEADERS) $^ $(LIBS) -o $@

clean:
	$(RM) main

