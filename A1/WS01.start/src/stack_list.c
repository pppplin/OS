#include <stack.h>
#include <list.h>
#include <stdlib.h>

#define STACK_SIZE 12

struct list_type* l;

int init_stack(){
	l = malloc(sizeof(struct list_type));
    init_list(l);
	return 0;
}

int push(void* element){
	insert_head(l, element);
	return 0;
}

void* pop(){
	void* content;
	content = extract_head(l);
	return content;
}


int size(){
	return list_size(l);
}

int get_stack_size(){
	return STACK_SIZE;
}
