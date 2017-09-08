#include <list.h>
#include <stdlib.h>
#include <stdio.h>


void init_list(struct list_type *l) {
	l->head = NULL;
	l->tail = NULL;
    /*for question7
    l->size = 0;*/
}
	
	
void insert_head(struct list_type *l, void* element) {
	cell* new_cell = malloc(sizeof(cell));
	new_cell->content = element;
	new_cell->previous = NULL;
	new_cell->next = l->head;
    if (l->head != NULL)
		l->head->previous = new_cell;
	l->head = new_cell;
	if (l->tail == NULL)
		l->tail = l->head;
    /*for question7
    l->size += 1;*/
}


void* extract_head(struct list_type *l) {
	/* TODO */
	cell* cur;
	void* content;

	if (l->head == NULL){
		printf("No element in list.\n");
		exit(0);
	}
	
	cur = l->head;
	content = cur->content;
	l->head = l->head->next;
	free(cur);

	if (l->head == NULL){
		l->tail = NULL;
	}
    /*for question7
    l->size -= 1;*/
	return content;
}


void* extract_tail(struct list_type *l) {
	/* TODO */
	cell* cur;
	void* content;
	if (l->tail==NULL){
		printf("No element in list.\n");
		exit(0);
	}

	cur = l->tail;
	content = cur->content;
	l->tail = l->tail->previous;
	free(cur);
	
	if (l->tail == NULL){
		l->head = NULL;
	}
    /*for question7
    l->size -= 1;*/
	return content;
}


int list_size(struct list_type *l) {
	/* TODO */
	int size = 0;
	cell* cur = l->head;
	if (cur!=NULL){
        size += 1;
		while (cur->next!=NULL){
			size += 1;
			cur = cur->next;
		}
	}
	return size;
}
	
