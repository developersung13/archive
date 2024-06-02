CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: sim

sim: sim.o fifo.o nru.o
	$(CC) $(CFLAGS) -o sim sim.o fifo.o nru.o

sim.o: sim.c fifo.h nru.h access.h
	$(CC) $(CFLAGS) -c sim.c

fifo.o: fifo.c fifo.h access.h
	$(CC) $(CFLAGS) -c fifo.c

nru.o: nru.c nru.h access.h
	$(CC) $(CFLAGS) -c nru.c

clean:
	rm -f sim *.o

