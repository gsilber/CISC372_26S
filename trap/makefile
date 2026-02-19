FLAGS=

all: trap_serial trap_mpi_1 trap_mpi_2

trap_serial: trap_serial.o function.o
	gcc $(FLAGS) trap_serial.o function.o -o trap_serial
trap_mpi_1: trap_mpi_1.o function.o
	mpicc $(FLAGS) trap_mpi_1.o function.o -o trap_mpi_1
trap_mpi_2: trap_mpi_2.o function.o
	mpicc $(FLAGS) trap_mpi_2.o function.o -o trap_mpi_2

trap_serial.o: trap_serial.c function.h
	gcc $(FLAGS) -c trap_serial.c
trap_mpi_1.o: trap_mpi_1.c function.h
	mpicc $(FLAGS) -c trap_mpi_1.c
trap_mpi_2.o: trap_mpi_2.c function.h
	mpicc $(FLAGS) -c trap_mpi_2.c

function.o: function.c
	gcc $(FLAGS) -c function.c

clean:
	rm -f trap_serial trap_mpi_1 trap_mpi_2 *.o
