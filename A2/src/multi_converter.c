#include <converters.h>
#include <string.h>
#include <sys/wait.h>

#define N 5

int main(int argc, char* argv[])
{
	int i;
	char* src_currency;
	char* target_currency[5] = {"EUR", "GBP", "USD", "JPY", "CNY"};
    float src_amount;
	float target_amount;
    
	strcpy(src_currency, argv[1]);
	src_amount = atof(argv[2]);
    
    int pid;
    for (i=0;i<N;i++){
        pid = fork();
        switch (pid){
            case -1:
                perror("E: \n");
                exit(1);
            case 0:
                target_amount = convert(src_currency, target_currency[i], src_amount);
                display_result(i, target_amount);
                exit(0);
        }

    }

    int j;
    for (j=0;j<N;j++){
        wait(0);
    }
    printf("End of conversion\n");
	return 0;
}








