MCC = mpicc
CC = gcc
CFLAGS = -Wall 
LDFLAGS = -lm

TARGETS = matrix_serial
all: $(TARGETS)

matrix_serial: matrix_serial.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c matrix.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGETS)

