Gameoflife.exe: main.o read.o gen.o imagen.o lodepng.o
	    $(CC) -o Gameoflife read.o main.o gen.o imagen.o lodepng.o

main.o: read.h gen.h imagen.h
	$(CC) -c main.c

imagen.o: read.h lodepng.h
	$(CC) -c imagen.c

read.o: read.h
	$(CC) -c  read.c 

gen.o: read.h
	$(CC) -c  gen.c

lodepng.o: lodepng.h
	$(CC) -c lodepng.c

.PHONY: clean

clean:
	-rm *.o -f Gameoflife result/* *.gch

test:
	./Gameoflife
