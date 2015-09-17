CC = gcc
CFLAGS = -g -c 
PROG = autcel

c_proximo: src/proximo.c
	$(CC) $(CFLAGS) src/proximo.c

as_proximo: src/proximo.S
	$(CC) $(CFLAGS) src/proximo.S

tp1_orga: src/main.c
	$(CC) $(CFLAGS) src/main.c

mips: as_proximo tp1_orga
	$(CC) proximo.o src/main.c -o $(PROG)

c: c_proximo tp1_orga
	$(CC) proximo.o src/main.c -o $(PROG)
	
clean:
	rm -rf *.o $(PROG)
