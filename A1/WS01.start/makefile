CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src

all: run

${OBJ}/stack_array.o: ${INC}/stack.h ${SRC}/stack_array.c
	${CC} -c -o ${OBJ}/stack_array.o -D STACK_SIZE=5 ${SRC}/stack_array.c -I${INC}

${OBJ}/stack_test.o: ${INC}/stack.h ${SRC}/stack_test.c
	${CC} -c -o ${OBJ}/stack_test.o ${SRC}/stack_test.c -I${INC}

${BIN}/stack_test1: ${OBJ}/stack_test.o ${LIB}/libstack1.a 
	${CC} -o $@ $^

${LIB}/libstack1.a: ${OBJ}/stack_array.o	
	ar rcs $@ $^

#question1-3
run1: ${BIN}/stack_test1
	echo "Testing Stack(array)"
	${BIN}/stack_test1


${OBJ}/list_impl.o: ${SRC}/list_impl.c ${INC}/list.h
	${CC} -c -o $@ $< -I${INC}
	
${OBJ}/stack_list.o: ${SRC}/stack_list.c ${INC}/stack.h ${INC}/list.h ${OBJ}/list_impl.o
	${CC} -c -o $@ $< -I${INC}

${LIB}/libstack2.a: ${OBJ}/stack_list.o ${OBJ}/list_impl.o
	ar rcs $@ $^

${BIN}/stack_test2: ${OBJ}/stack_test.o ${LIB}/libstack2.a
	${CC} -o $@ $^

#question5
run2: ${BIN}/stack_test2
	echo "Testing Stack(list)"
	${BIN}/stack_test2


${OBJ}/fifo_list.o: ${SRC}/fifo_list.c ${INC}/fifo.h
	${CC} -c -o $@ $< -I${INC}

${LIB}/libfifo.a: ${OBJ}/fifo_list.o ${OBJ}/list_impl.o
	ar rcs $@ $^

${OBJ}/fifo_test.o: ${SRC}/fifo_test.c ${INC}/fifo.h
	${CC} -c -o $@ $< -I${INC}

${BIN}/stack_test3: ${OBJ}/fifo_test.o ${LIB}/libfifo.a
	${CC} -o $@ $^

#question6
run3: ${BIN}/stack_test3
	echo "Testing Queue(list)"
	${BIN}/stack_test3


run: run1 run2 run3

clean:
	rm -f ${OBJ}/* ${BIN}/* ${LIB}/*
