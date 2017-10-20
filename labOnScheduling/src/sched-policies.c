#include <os-scheduling.h>


void print_queues(task tasks[], sched_data* schedData) {
    int i, j, taskIndex = 0;
    printf("Nb of queues %d\n", schedData->nbOfQueues);
    for (i = 0; i < schedData->nbOfQueues; i++) {
        j = 0;
        printf("Q%d => ", i);
        while (j < MAX_NB_OF_TASKS) {
            taskIndex = schedData->queues[i][j];
            if (taskIndex == -1) {
                j = MAX_NB_OF_TASKS;
            } else {
                printf("%s ", tasks[taskIndex].name);
                j++;
            }
        }
        printf("\n");
    }
}


int FCFS(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime) {
    int i, j;

    // Initialize single queue
    if (currentTime == 0) {
        printf("Initializing job queue\n");
        schedData->nbOfQueues = 1;
        for (i = 0; i < MAX_NB_OF_TASKS; i++) {
            schedData->queues[0][i] = -1;
        }
    }

    // Admit new tasks (currentTime >= arrivalTime)
    j = 0;
    while (schedData->queues[0][j] != -1)
        j++;
    for(i = 0; i < nbOfTasks; i++) {
        if ((tasks[i].state == UPCOMING) && (tasks[i].arrivalDate == currentTime)) {
            tasks[i].state = READY;
            schedData->queues[0][j] = i;
            j++;
        }
    }
    print_queues(tasks, schedData);

    // Is the first task in the queue running? Has that task finished its computations?
    //   If so, put it in terminated state and remove it from the queue
    //   If not, continue this task
    i = schedData->queues[0][0];
    if (i != -1) {
        if (tasks[i].state == RUNNING) {
            if (tasks[i].executionTime == tasks[i].computationTime) {
                tasks[i].state = TERMINATED;
                tasks[i].responseTime = currentTime - tasks[i].arrivalDate;
                tasks[i].penaltyrate = (double)tasks[i].responseTime/tasks[i].computationTime;
                tasks[i].waitingTime = tasks[i].responseTime - tasks[i].computationTime;

                for (j = 0; j < MAX_NB_OF_TASKS - 1; j++) {
                    schedData->queues[0][j] = schedData->queues[0][j+1];
                }
            } else {
                /* Reelect this task */
                tasks[i].executionTime ++;
                return i;
            }
        }
    }

    // Otherwise, elect the first task in the queue
    i = schedData->queues[0][0];
    if (i != -1){
        tasks[i].executionTime ++;
        tasks[i].state = RUNNING;
        return i;
    }

    // No task could be elected
    return -1;
}


int SJF(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime) {
    //init
    int i, j, k;
    if (currentTime == 0){
        printf("Initializing job queue\n");
        schedData->nbOfQueues = 1;
        for (i=0; i<MAX_NB_OF_TASKS; i++){
            schedData->queues[0][i] = -1;
        }
    }

    //non-preemptive
    for (i=0; i<nbOfTasks; i++){
        if ((tasks[i].state == UPCOMING) && (tasks[i].arrivalDate == currentTime)){
            tasks[i].state = READY;
            if (schedData->queues[0][0]==-1){
                schedData->queues[0][0] = i;
            }else{
                j = 1;
                //insert from second if first running
                while ((schedData->queues[0][j]!=-1) && (tasks[schedData->queues[0][j]].computationTime<=tasks[i].computationTime))
                    j++;
                for (k=MAX_NB_OF_TASKS;k>j;k--){
                    schedData->queues[0][k] = schedData->queues[0][k-1];
                }
                schedData->queues[0][j] = i;
            }
        }
    }
    print_queues(tasks, schedData);

    //terminate n reselect, first one running
    i = schedData->queues[0][0];
    int n = -1;
    if (i!=-1){
        if (tasks[i].executionTime == tasks[i].computationTime){
            tasks[i].state = TERMINATED;
            tasks[i].responseTime = currentTime - tasks[i].arrivalDate;
            tasks[i].penaltyrate = (double)tasks[i].responseTime/tasks[i].computationTime;
            tasks[i].waitingTime = tasks[i].responseTime - tasks[i].computationTime;

            for (j=0;j<MAX_NB_OF_TASKS-1; j++)
                schedData->queues[0][j] = schedData->queues[0][j+1];
            n = schedData->queues[0][0];
            if (n!=-1){
                tasks[n].state = RUNNING;
                tasks[n].executionTime++;
            }
            return n;
        }
        else{
            tasks[i].state = RUNNING;
            tasks[i].executionTime++;
            return i;
        }
    }
    return -1;
}

// SJF preemptive
int SRTF(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime) {
    int i, j, k;
    if (currentTime == 0){
        printf("Initializing job queue\n");
        schedData->nbOfQueues = 1;
        for (i=0; i<MAX_NB_OF_TASKS; i++){
            schedData->queues[0][i] = -1;
        }
    }

    //when insert
    for(i = 0; i < nbOfTasks; i++) {
        if (tasks[i].state == RUNNING){
            if (tasks[i].remainTime==0){
                tasks[i].state = TERMINATED;
                tasks[i].responseTime = currentTime - tasks[i].arrivalDate;
                tasks[i].penaltyrate = (double)tasks[i].responseTime/tasks[i].computationTime;
                tasks[i].waitingTime = tasks[i].responseTime - tasks[i].computationTime;
                for (j=0;j<MAX_NB_OF_TASKS-1;j++)
                    schedData->queues[0][j] = schedData->queues[0][j+1];
            }else
                tasks[i].state = READY;
        }

        if (tasks[i].arrivalDate == currentTime) {
            tasks[i].state = READY;
            tasks[i].remainTime = tasks[i].computationTime;
            j = 0;
            while ((schedData->queues[0][j]!=-1) && (tasks[schedData->queues[0][j]].remainTime<=tasks[i].remainTime))
                j++;
            for (k=MAX_NB_OF_TASKS;k>j;k--)
                schedData->queues[0][k] = schedData->queues[0][k-1];
            schedData->queues[0][j] = i;
        }
    }
    print_queues(tasks, schedData);

    //switch: first one running
    i = schedData->queues[0][0];
    if (i!=-1) {
        tasks[i].state = RUNNING;
        tasks[i].executionTime++;
        tasks[i].remainTime--;
        return i;
    }
    return -1;
}

int RR(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime, int q) {
    int i, j;

    // Initialize single queue
    if (currentTime == 0) {
        printf("Initializing job queue\n");
        schedData->nbOfQueues = 1;
        for (i = 0; i < MAX_NB_OF_TASKS; i++) {
            schedData->queues[0][i] = -1;
        }
    }

    // Admit new tasks (currentTime == arrivalTime)
    j = 0;
    while (schedData->queues[0][j] != -1)
        j++;
    for(i = 0; i < nbOfTasks; i++) {
        if (tasks[i].arrivalDate == currentTime){
            tasks[i].state = READY;
            tasks[i].remainTime = q;
            schedData->queues[0][j] = i;
            j++;
        }
    }
    print_queues(tasks, schedData);

    i = schedData->queues[0][0];
    if (i != -1) {
        if (tasks[i].executionTime == tasks[i].computationTime) {
            tasks[i].state = TERMINATED;
            tasks[i].responseTime = currentTime - tasks[i].arrivalDate;
            tasks[i].penaltyrate = (double)tasks[i].responseTime/tasks[i].computationTime;
            tasks[i].waitingTime = tasks[i].responseTime - tasks[i].computationTime;

            for (j = 0; j < MAX_NB_OF_TASKS - 1; j++) {
                schedData->queues[0][j] = schedData->queues[0][j+1];
            }
        } else if (tasks[i].remainTime==0){
            //end of quantum
            j = 0;
            while ((schedData->queues[0][j+1]!=-1) && (j<MAX_NB_OF_TASKS - 1)) {
                schedData->queues[0][j] = schedData->queues[0][j+1];
                j++;
            }
            schedData->queues[0][j] = i;
            tasks[i].remainTime = q;
            tasks[i].state = READY;
        }
        i = schedData->queues[0][0];
        if (i!=-1){
            tasks[i].executionTime ++;
            tasks[i].state = RUNNING;
            tasks[i].remainTime --;
            return i;
        }
    }
    return -1;
}

int MFQ(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime, int q) {
    int i, j, k;

    // Initialize single queue
    if (currentTime == 0) {
        printf("Initializing job queue\n");
        schedData->nbOfQueues = 3;
        for (j=0; j<schedData->nbOfQueues; j++){
            for (i = 0; i < MAX_NB_OF_TASKS; i++) {
                schedData->queues[j][i] = -1;
            }
        }
    }

    // Admit new tasks (currentTime == arrivalTime)
    j = 0;
    while (schedData->queues[0][j] != -1)
        j++;
    for(i = 0; i < nbOfTasks; i++) {
        if (tasks[i].arrivalDate == currentTime){
            tasks[i].state = READY;
            tasks[i].remainTime = q;
            schedData->queues[0][j] = i;
            j++;
        }
    }
    print_queues(tasks, schedData);

    j = 1;
    i = schedData->queues[0][0];
    while ((i==-1) && (i<schedData->nbOfQueues)){
        i = schedData->queues[j][0];
        j++;
    }

    //rearrange and select
    if (i != -1) {
        if (tasks[i].executionTime == tasks[i].computationTime) {
            tasks[i].state = TERMINATED;
            tasks[i].responseTime = currentTime - tasks[i].arrivalDate;
            tasks[i].penaltyrate = (double)tasks[i].responseTime/tasks[i].computationTime;
            tasks[i].waitingTime = tasks[i].responseTime - tasks[i].computationTime;
            for (k = 0; k < MAX_NB_OF_TASKS - 1; k++) {
                schedData->queues[j-1][k] = schedData->queues[j-1][k+1];
            }
        } else if (tasks[i].remainTime==0){
            //end of quantum
            for(k=0;k<MAX_NB_OF_TASKS - 1;k++) {
                schedData->queues[j-1][k] = schedData->queues[j-1][k+1];
            }

            j = j/3;
            k = 0;
            while (schedData->queues[j][k]!=-1)
                k++;
            schedData->queues[j][k] = i;
            tasks[i].remainTime = q*(j+1);
            tasks[i].state = READY;
        }

        j = 1;
        i = schedData->queues[0][0];
        while ((i==-1) && (j<schedData->nbOfQueues)){
            i = schedData->queues[j][0];
            j++;
        }
        if (i!=-1){
            tasks[i].executionTime ++;
            tasks[i].state = RUNNING;
            tasks[i].remainTime --;
            return i;
        }
    }
    return -1;
}

int IORR(task tasks[], int nbOfTasks, sched_data* schedData, int currentTime, int q) {
    int i, j, k;

    // Initialize single queue
    if (currentTime == 0) {
        printf("Initializing job queue\n");
        schedData->nbOfQueues = 1;
        for (i = 0; i < MAX_NB_OF_TASKS; i++) {
            schedData->queues[0][i] = -1;
        }
    }

    // Admit new tasks (currentTime == arrivalTime)
    j = 0;
    while (schedData->queues[0][j] != -1)
        j++;
    for(i = 0; i < nbOfTasks; i++) {
        if (tasks[i].arrivalDate == currentTime){
            tasks[i].state = READY;
            tasks[i].remainTime = q;
            tasks[i].IO = 0;
            schedData->queues[0][j] = i;
            j++;
        }
    }
    print_queues(tasks, schedData);

    //get running task
    j = 0;
    while ((schedData->queues[0][j]!=-1) && (tasks[schedData->queues[0][j]].state !=RUNNING)) 
        j++;
    i = schedData->queues[0][j];
    
    //IO
    for(k = 0; k < nbOfTasks; k++){
        if (tasks[k].IO == 1){
            tasks[k].remainIOTime --;
            if (tasks[k].remainIOTime==0)
                tasks[k].IO = 0;
        }
    }
    
    //rearrange queue
    if (i != -1) {
        if ((tasks[i].executionTime == tasks[i].computationTime) && (tasks[i].remainIOTime ==0)) {
            tasks[i].state = TERMINATED;
            tasks[i].responseTime = currentTime - tasks[i].arrivalDate;
            tasks[i].penaltyrate = (double)tasks[i].responseTime/tasks[i].computationTime;
            tasks[i].waitingTime = tasks[i].responseTime - tasks[i].computationTime;
            for (j = 0; j < MAX_NB_OF_TASKS - 1; j++) {
                schedData->queues[0][j] = schedData->queues[0][j+1];
            }
        } else if ((tasks[i].TimeToIO==0)|| (tasks[i].remainTime == 0)){
            //request IO
            j = 0;
            while ((schedData->queues[0][j+1]!=-1) && (j<MAX_NB_OF_TASKS - 1)) {
                schedData->queues[0][j] = schedData->queues[0][j+1];
                j++;
            }
            schedData->queues[0][j] = i;
            tasks[i].state = READY;
            if (tasks[i].TimeToIO==0)
                tasks[i].IO = 1;
        }
    }

    //select
    j = 0;
    while ((schedData->queues[0][j]!=-1) && (tasks[schedData->queues[0][j]].IO==1))
        j++;
    i = schedData->queues[0][j];
    if (i!=-1){
        tasks[i].executionTime ++;
        tasks[i].state = RUNNING;
        tasks[i].remainTime --;
        tasks[i].TimeToIO--;
        return i;
    }

    return -1;
}
