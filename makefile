CC = gcc
CFLAGS = -g -Wall

all: tp3

tp3: tp3.o TAD_text.o TAD_paradigms.o
	$(CC) $(CFLAGS) tp3.o TAD_text.o TAD_paradigms.o -o tp3.exe -lm

tp3.o: tp3.c TAD_text.h TAD_paradigms.h
	$(CC) $(CFLAGS) -c tp3.c

TAD_text.o: TAD_text.h TAD_text.c
	$(CC) $(CFLAGS) -c TAD_text.c 

TAD_paradigms.o: TAD_paradigms.h TAD_paradigms.c
	$(CC) $(CFLAGS) -c TAD_paradigms.c 	

clean:
	rm -f tp3.exe tp3.o TAD_text.o TAD_paradigms.o
