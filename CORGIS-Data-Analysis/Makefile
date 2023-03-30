CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -g -lm
MAIN = corgis
OBJS = corgis.o

all: $(MAIN)

$(MAIN) : $(OBJS) corgis.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

corgis.o: corgis.c corgis.h
	$(CC) $(CFLAGS) -c corgis.c