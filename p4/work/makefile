nn: nn.o file.o
	gcc nn.o file.o -o nn -lm
nn.o: nn.c file.h config.h
	gcc -c nn.c -o nn.o
file.o: file.c file.h
	gcc -c file.c -o file.o

clean:
	rm -f nn nn.o file.o