objects = FIFO.o

edit : $(objects)
	cc -o edit $(objects)
FIFO.o : FIFO.c common.h FIFO.h
	cc -c FIFO.c
clean :
	rm edit $(objects)