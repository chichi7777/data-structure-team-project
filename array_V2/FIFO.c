#include <stdio.h>
#include <stdlib.h>
#include "project.h"

int running_with_FIFO (char * filename, quType * doneQ)
{
	int time;
	float utilization=0.0;
    pType * p;;
    quType * jobQ, * readyQ;

    jobQ = newQueue();
    readyQ = newQueue();

    readFile (filename, jobQ);

    time = 0;
    while (jobQ->count != 0 || readyQ->count != 0) {		//end loop if all the processes is finished
        setReadyQ (readyQ, jobQ, time);
        p = FIFO (readyQ,doneQ,time);
        showPrsRun(time,p,&utilization);
        time++;
    }
 
    printf("\n Total run time: %d\n",time);
	printf(" Utilization: %f %%\n",(float)((utilization*100)/time));
	sortQ_with_arrivalTime (doneQ);
    return 0;
}

pType * FIFO(quType*q,quType*doneQ,int time)
{
    pType * temp;
    if(q->count>0){
        front(q)->remainingTime--;
        if(front(q)->remainingTime<=0){			//count waiting time,turnaround time...and store into doneQ
            temp = dequeue(q);
            temp->waitingTime=time-temp->arrivalTime-temp->burstTime+1;
            temp->turnaroundTime=time-(temp->arrivalTime)+1;
            temp->responseTime=temp->waitingTime;
            enqueue(doneQ , temp);
            return temp;
        }
        else {
            return front(q);
        }
    }
    else return NULL;
}
