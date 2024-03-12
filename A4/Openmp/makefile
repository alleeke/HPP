CFLAGS=-Wall
INCLUDES=-I/opt/X11/include -Igraphics
LDFLAGS=-L/opt/X11/lib -lX11 -lm

galsim: galsim.o graphics.o
	gcc -o galsim galsim.o graphics.o -fopenmp $(LDFLAGS)

galsim.o: galsim.c
	gcc -fopenmp $(CFLAGS) $(INCLUDES) -c galsim.c

graphics.o: graphics/graphics.c graphics/graphics.h
	gcc -fopenmp $(CFLAGS) $(INCLUDES) -c graphics/graphics.c

clean:
	rm -f ./galsim *.o
