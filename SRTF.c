#include <stdio.h>
#include <stdlib.h>
#include "project.h"

int running_with_SRTF(char * filename, quType * doneQ)
{    
    int time;
    float utilization=0.0;
    pType * p;
    quType * jobQ, * readyQ;

    jobQ = newQueue();
    readyQ = newQueue();

    readFile (filename, jobQ);

    time = 0;
    while (jobQ->count != 0 || readyQ->count != 0) {		//end loop if all the processes is finished
        if (setReadyQ (readyQ, jobQ, time) == 1) {			//check if another process comes with shorter burst time comes in
            sortQ_with_remainingTime (readyQ);
        }
        p = SRTF (readyQ, doneQ, time);
        showPrsRun (time, p, &utilization);
        time++;
    }

	printf("\n Total run time: %d\n",time);
	printf(" Utilization: %f %%\n",(float)((utilization*100)/time));
	sortQ_with_arrivalTime (doneQ);
    return 0;
}
         
pType * SRTF (quType * readyQ, quType * doneQ, int time)
{
    pType * p;

    if (readyQ->count > 0) {
        p = front(readyQ);
        if (p->remainingTime == p->burstTime) {			//count response time
            p->responseTime = time - p->arrivalTime;
        }
        p->remainingTime--;
        if (p->remainingTime <= 0) {					//count waiting time, turnatound time...and store into doneQ
            p->waitingTime = time + 1 - p->arrivalTime - p->burstTime;
            p->turnaroundTime = time + 1 -p->arrivalTime;
            enqueue (doneQ, dequeue(readyQ));
        }
        return p;
    }
    else return NULL;
}

