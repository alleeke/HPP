

SOURCES := $(wildcard *.c)

EXECUTABLES := $(SOURCES:.c=)

OPTIMIZATION :=

all: $(EXECUTABLES)

%: %.c
	gcc $(OPTIMIZATION) -o $@ $<

O1: OPTIMIZATION = -O1
O1: all

O2: OPTIMIZATION = -O2
O2: all

O3: OPTIMIZATION = -O3
O3: all


clean:
	rm -f $(EXECUTABLES)