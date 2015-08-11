CC = gcc
CXX = icpc
CFLAGS = -std=c99 -g
TARGET = perf
SOURCE = main.c

default: compile client run

compile: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${SOURCE} -o ${TARGET} ${LDFLAGS}

client: client.c
	${CC} ${CFLAGS} client.c -o client ${LDFLAGS}

run:
	python echo-server.py
    
