objects = FIFO.o testing.o

edit : $(objects)
	cc -o edit $(objects)
FIFO.o : FIFO.c common.h FIFO.h
	cc -c FIFO.c
testing.o : testing.c common.h FIFO.h
	cc -c testing.c
clean :
	rm edit $(objects)