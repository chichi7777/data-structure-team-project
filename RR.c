#include <stdio.h>
#include <stdlib.h>
#include "project.h"

int running_with_RR(char * filename, quType * doneQ)
{
	int timeQuantum, currentTime = 0;
	float utilization=0.0;
    quType * jobQ, * readyQ;

    jobQ = newQueue();
    readyQ = newQueue();

    printf(" Time quantum = ");
    scanf("%d", &timeQuantum);
    printf("\n");

    readFile (filename,jobQ);

    setReadyQ2 (readyQ, jobQ, currentTime, 0);

    while (jobQ->count != 0 || readyQ->count != 0){
        currentTime += RR (jobQ, readyQ, doneQ, currentTime, timeQuantum, &utilization);
    }
    printf("\n Total run time: %d\n",currentTime);
	printf(" Utilization: %f %%\n",(float)((utilization*100)/currentTime));
	sortQ_with_arrivalTime (doneQ);
}

int RR (quType * jobQ, quType * readyQ, quType * doneQ, int currentTime, int timeQuantum, float *utilization)
{

    if (readyQ->count > 0) {
            pType * p = readyQ->front->p;

            if(p->flag == 0){     //determine whether this is the first time the operation gain attention from the CPU
                p->flag = 1;
                p->responseTime = currentTime - p->arrivalTime;
            }

            if(p->remainingTime > timeQuantum)
            {
                showPrsRun2 (currentTime, timeQuantum, p, utilization);

                setReadyQ2 (readyQ, jobQ, currentTime, timeQuantum);     //enquType operations during a period of time
                p = dequeue(readyQ);
                (p->remainingTime) -= timeQuantum;
                enqueue(readyQ, p);

                return timeQuantum;
            }

            else{
                showPrsRun2 (currentTime, p->remainingTime, p, utilization);

                p = dequeue(readyQ);
                schedule(doneQ, p, currentTime);
                setReadyQ2 (readyQ, jobQ, currentTime, p->remainingTime);

                return p->remainingTime;
            }

    }

    else{
        showPrsRun2(currentTime, 1, NULL, utilization);
        setReadyQ2 (readyQ, jobQ, currentTime, 1);
        return 1;
    }
}

