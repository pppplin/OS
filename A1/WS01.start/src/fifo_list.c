#include <fifo.h>
#include <list.h>
#include <stdlib.h>

struct list_type* l;

int init_queue(){
    l = malloc(sizeof(struct list_type));
    init_list(l);
    return 0;
}

int queue(void* element){
    insert_head(l, element);
    return 0;
}

void* dequeue(){
    void* content;
    content = extract_tail(l);
    return content;
}

int size(){
    return list_size(l);
} 
