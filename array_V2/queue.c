#include <stdio.h>
#include <stdlib.h>
#include "project.h"

quType * newQueue()
{
    quType * q = malloc(sizeof(quType));
    q->count = 0;
    return q;
}

int enqueue (quType * q, pType * p)	//push item into queue
{
    if (q->count < SIZE) {
        if (q->count == 0) {
            q->p[0] = p;
            q->front = 0;
            q->rear = 0;
            q->count = 1;
        }
        else {
            q->rear++;
            q->rear = q->rear % SIZE;
            q->p[q->rear] = p;
            q->count++;
        }
        return 1;
    }
    else return 0;
}

pType * dequeue (quType * q)			//remove item from queue
{
    pType * p;

    if (q->count != 0) {
        p = q->p[q->front];
        q->p[q->front] = NULL;
        q->front++;
        q->front = q->front % SIZE;
        q->count--;
        return p;
    }
    else return NULL;
}

pType * front (quType * q)			//return the front item of queue
{
    if (q->count != 0) {
        return q->p[q->front];
    }
    else return NULL;
}
