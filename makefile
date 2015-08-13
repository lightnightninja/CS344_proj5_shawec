CC = gcc
CXX = icpc
CFLAGS = -std=c99 -g
TARGET = prog
SOURCE = main.c

default: compile client

compile: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${SOURCE} -o ${TARGET} ${LDFLAGS}

client: client.c
	${CC} ${CFLAGS} client.c -o client ${LDFLAGS}

manage:
    python manage.py

report:
    python report.py