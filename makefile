CC = gcc

all: myheal mybreak

myheal: myheal.c
	$(CC) -o myheal myheal.c

mybreak: mybreak.c
	$(CC) -o mybreak mybreak.c
