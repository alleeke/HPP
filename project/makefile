CFLAGS = -O3 -Wall -Werror
SOURCE = main.c quick_sort.c 
EXECUTABLE = quick_sort

all:$(EXECUTABLE)

$(EXECUTABLE): $(SOURCE)
	gcc $(SOURCE) -o $(EXECUTABLE)

clean:
	rm $(EXECUTABLE)