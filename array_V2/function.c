#include <stdio.h>
#include <stdlib.h>
#include "project.h"

void readFile (char * filename, quType * jobQ)		//read text file and store data into jobQ
{
    FILE * fp = fopen(filename, "r");
    int ID, arrivalTime, burstTime;
    pType * p;

    while (fscanf(fp,"%d %d %d", &ID, &arrivalTime, &burstTime) != EOF) {
        p = malloc(sizeof(pType));
        p->ID = ID;
        p->arrivalTime = arrivalTime;
        p->burstTime = burstTime;
        p->remainingTime = burstTime;
        enqueue (jobQ, p);
    }
    fclose(fp);
}

int setReadyQ (quType * readyQ, quType * jobQ, int time)		//move item from jobQ to readyQ
{
    if (jobQ->count > 0) {
        if (front(jobQ)->arrivalTime == time) {
            enqueue (readyQ, dequeue(jobQ));
            return 1;
        }
    }
    else return 0;
}

void setReadyQ2 (quType * readyQ, quType * jobQ, int currentTime, int elapsedTime)	//for Round Robin
{
    pType * p;

    for(int time = currentTime; time <= currentTime + elapsedTime; time++)
        if(jobQ->count > 0)
            if(front(jobQ)->arrivalTime == time) {
                p = dequeue (jobQ);
                enqueue (readyQ, p);
        }

    return;

}

int showPrsRun (int time, pType * p, float *utilization)		//show the process running at the moment
{
    if (p != NULL) {
        printf(" Time: %2d ~ %2d, Performing P%d\n", time, time+1, p->ID);
        *utilization+=1.0;
        return 1;
    }
    else {
        printf(" Time: %2d ~ %2d,       X   \n", time, time+1);
        return 0;
    }
}

void showPrsRun2 (int time, int elapsedTime, pType * p, float *utilization)
{
    if (p != NULL) {
        printf(" Time: %2d ~ %2d, Performing P%d \n", time, time + elapsedTime, p->ID);
        *utilization+=elapsedTime;
	}
    else
        printf(" Time: %2d ~ %2d,        X   \n", time, time + 1);
}

void sortQ_with_remainingTime (quType * q)
{
    pType * temp;
    int i,j;

    // reset : move data to the front of array (q->front == 0)
    if(q->front != 0) {
        if(q->front <= q->rear) {
            for(i=0; i < q->count; i++) {
                q->p[i] = q->p[q->front + i];
            }
        }
        else {
            for(i=0; i < SIZE - q->front; i++) {
                q->p[q->rear +1 +i] = q->p[q->front + i];
            }
        }
    }
    q->front = 0;
    q->rear = q->count - 1;

    // insertion sort
    for(i=1; i < q->count; i++) {
        temp = q->p[i];
        for(j=i; j > 0 && q->p[j-1]->remainingTime > temp->remainingTime; j--) {
            q->p[j] = q->p[j-1];
        }
        q->p[j] = temp;
    }
}

void sortQ_with_arrivalTime (quType * q)
{
    pType * temp;
    int i,j;

    // reset : move data to the front of array (q->front == 0)
    if(q->front != 0) {
        if(q->front <= q->rear) {
            for(i=0; i < q->count; i++) {
                q->p[i] = q->p[q->front + i];
            }
        }
        else {
            for(i=0; i < SIZE - q->front; i++) {
                q->p[q->rear +1 +i] = q->p[q->front + i];
            }
        }
    }
    q->front = 0;
    q->rear = q->count - 1;

    // insertion sort
    for(i=1; i < q->count; i++) {
        temp = q->p[i];
        for(j=i; j > 0 && q->p[j-1]->arrivalTime > temp->arrivalTime; j--) {
            q->p[j] = q->p[j-1];
        }
        q->p[j] = temp;
    }
}

void printResult(quType * q)			//print the results of all processes
{
    for(int i=0; i<q->count; i++) {
    	printf("\n P%d: Response time = %2d, Turnaround time = %2d, Waiting time = %2d", q->p[i]->ID, q->p[i]->responseTime, q->p[i]->turnaroundTime, q->p[i]->waitingTime);
    	
    }
    printf("\n");

}

void schedule(quType * doneQ, pType * p, int currentTime)
{
    p->turnaroundTime = currentTime + p->remainingTime - p->arrivalTime;
    p->waitingTime = p->turnaroundTime - p->burstTime;
    enqueue(doneQ, p);
}

aveType printAverageTime(quType*q)		//print average waiting time,response time,turnaround time
{
    pType*p;
    aveType ave;
    int tot_waitingTime=0,tot_turnaroundTime=0,tot_responseTime=0;
    int count=q->count;
    while(q->count>0)
    {
        p=dequeue(q);
        tot_waitingTime+=p->waitingTime;
        tot_turnaroundTime+=p->turnaroundTime;
        tot_responseTime+=p->responseTime;

    }
    ave.waitTime = ((float)tot_waitingTime/(float)count);
    ave.respTime = ((float)tot_responseTime/(float)count);
    ave.turnardTime = ((float)tot_turnaroundTime/(float)count);
	printf("\n Average waiting time: %f",ave.waitTime);
    printf("\n Average response time: %f",ave.respTime);
    printf("\n Average turnaround time: %f\n\n",ave.turnardTime);
    
    return ave;
}
