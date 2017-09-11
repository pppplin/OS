CC=gcc -Wall -ansi -std=c99
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src

all: run

${OBJ}/process.o: ${SRC}/process.c
	${CC} -c -o ${OBJ}/process.o ${SRC}/process.c -I${INC} 

${OBJ}/process_test.o: ${SRC}/process_test.c
	${CC} -c -o ${OBJ}/process_test.o ${SRC}/process_test.c -I${INC} 

${BIN}/process: ${OBJ}/process.o ${OBJ}/process_test.o
	${CC} -o $@ $^


run: ${BIN}/process
	echo "Testing"
	${BIN}/process

clean:
	rm -f ${OBJ}/* ${BIN}/* ${LIB}/*
