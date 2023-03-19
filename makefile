SHELL = /bin/bash
CC = gcc
CFLAGS = -g -pthread
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE} run

%:	%.c
	${CC} ${CFLAGS} $@.c -o $@

clean:
	rm ${EXE} flock.db lockf.db
mount:
	sudo mount -oremount, mand /
	chmod g+s ./lockf.db
	chmod g-x ./lockf.db

run_flock:
	time ./flock & time ./flock & time ./flock & time ./flock

run_lockf:
	time ./flock & time ./flock & time ./flock & time ./flock

run:
	echo -n "3500" > flock.db
	echo -n "3500" > lockf.db 

