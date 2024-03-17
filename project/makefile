CFLAGS = -g -O3 -Wall -Werror
LDFLAGS = -fopenmp
SOURCE = main.c quick_sort.c quick_sort_parallel.c
EXECUTABLE = quick_sort

all:$(EXECUTABLE)

$(EXECUTABLE): $(SOURCE)
	gcc ${CFLAGS} ${LDFLAGS} $(SOURCE) -o $(EXECUTABLE)

clean:
	rm $(EXECUTABLE)