january: part3.c
	gcc -Wall -o january part3.c

part3G: part3.c
	gcc -Wall -g part3.c -o part3

valgrind: part3G
	valgrind --leak-check=full ./part3G

clean: 
	rm -f january
