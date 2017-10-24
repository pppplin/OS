/**** decoder.c ****/

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
/*#include <decoder.h>*/


#define _XOPEN_SOURCE 700

int check();
void display();
int solve(int x); 

int magicsq[3][3] = {{4, -1, 8}, {-1, -1, -1}, {2, -1, 6}};


int check() {
	int i, j, sums[8];
	for (i = 0; i < 8; i++) 
		sums[i] = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			sums[i] += magicsq[i][j];
			sums[i+3] += magicsq[j][i];
			if (i == j) sums[6] += magicsq[i][j];
			if ((i+j) == 2) sums[7] += magicsq[i][j];
		}
	}
	int result = 1;
	i = 1;
	while ((i < 8) && (result == 1)) {
		if (sums[0] != sums[i])
			result = 0;
		i++;
	}
	return result;
}


void display() {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++)
			printf("  %d", magicsq[i][j]);
		printf("\n");
	}
	printf("\n");
}


int solve(int x) {
	/* CODE THAT EVERY CHILD PROCESS EXECUTES */
	int sum, r, j;
	magicsq[0][1] = x;
	sum = 0;
	for (j=0;j<3;j++)
		sum += magicsq[0][j];

    magicsq[2][1] = sum-magicsq[2][0]-magicsq[2][2];
	magicsq[1][0] = sum-magicsq[0][0]-magicsq[2][0];
	magicsq[1][2] = sum-magicsq[0][2]-magicsq[2][2];
	magicsq[1][1] = sum-magicsq[1][0]-magicsq[1][2];
    
    int m, n;
	for (m = 0; m < 3; m++) {
		for (n = 0; n < 3; n++){
            if ((magicsq[m][n]<0) || (magicsq[m][n]>9))
                exit(0);
        }
    }

    r = check();
	if (r==1)
		display();
    exit(0);
}

int main(int argc, char **argv){	
	/* PARENT PROCESS*/
	int i;
    int pid;
    
    for (i=0;i<10;i++){
        pid = fork();
        switch (pid){
            case -1:
                perror("E:\n");
				exit(1);
            case 0:
                solve(i);
        }
    }

    return EXIT_SUCCESS;
}
