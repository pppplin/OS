CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src
ARG = default

all: run

${OBJ}/program_trace.o: ${SRC}/program_trace.c
	${CC} -c -o ${OBJ}/program_trace.o ${SRC}/program_trace.c

${BIN}/program_trace: ${OBJ}/program_trace.o 
	${CC} -o $@ $^

#question1
run1: ${BIN}/program_trace
	echo "testing program_trace"
	${BIN}/program_trace

${OBJ}/decoder.o: ${SRC}/decoder.c
	${CC} -c -o ${OBJ}/decoder.o ${SRC}/decoder.c

${BIN}/decoder: ${OBJ}/decoder.o 
	${CC} -o $@ $^


#question2
run2: ${BIN}/decoder
	echo "testing decoder"
	${BIN}/decoder


${OBJ}/converters.o: ${SRC}/converters.c ${INC}/converters.h
	${CC} -c -o $@ $< -I${INC}

${OBJ}/multi_converter.o: ${SRC}/multi_converter.c
	${CC} -c -o $@ $< -I${INC}

${BIN}/multi_converter: ${OBJ}/multi_converter.o ${OBJ}/converters.o
	${CC} -o $@ $^

#question3
run3: ${BIN}/multi_converter
	echo "Testing converter"
	${BIN}/multi_converter CNY 100.000

run: run1 run2 run3

clean:
	rm -f ${OBJ}/* ${BIN}/* ${LIB}/*




