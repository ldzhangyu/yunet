

CFLAGS = -g -Wall
GCC = gcc

#all: yunet

yunet:  main.c mempoll.c
	$(GCC) $(CFLAGS) -o $@ $^ 

clean:
	-rm yunet

