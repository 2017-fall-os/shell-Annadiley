all: shell
CFLAGS =-g -O2

shell: mytoc.o strcopy.o shell.o
	cc -o shell shell.o  mytoc.c strcopy.o
clean:
	rm *.o shell
run:
	./shell
