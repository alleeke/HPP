CC = gcc
CFLAGS = -Wall -Wextra

# Get a list of all .c files in the current directory
SOURCES := $(wildcard *.c)

EXECUTABLES := $(SOURCES:.c=)

all: $(EXECUTABLES)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLES) 
