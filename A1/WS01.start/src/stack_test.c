#include <stack.h>
#include <stdio.h>
#include <stdlib.h>
#include <list.h>

int main(int argc, char** argv) {
	printf("The STACK_SIZE is: %d\n", get_stack_size());

	char* mywords[4] = {"The Force", "is", "strong", "within this Jedi"};
	int i;
	int nb;
	
	init_stack();
	
	for(i = 0; i < 4; i++)
		push(mywords[i]);
	
	nb = size();
	
	printf("The size of the stack is %d\n", nb);
	for(i = 0; i < nb; i++)
		printf("%s \n", (char*)pop());

	return EXIT_SUCCESS;
}
