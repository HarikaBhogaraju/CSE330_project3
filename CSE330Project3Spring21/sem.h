//Harika Bhogaraju
//1216938606

#include <stdio.h>
#include <stdlib.h>
#include "threads.h"

typedef struct semaphore
{
    int value;
    struct q *s_q;
} semaphore;

//to initialize semaphores with given value
void initSem(semaphore *sem, int value)
{
    sem->s_q = (struct q*) malloc(sizeof(struct q));
    InitQueue(sem->s_q);
    sem->value = value;
}

//P semaphore
void P(semaphore *sem)
{
    struct TCB_t *tcb;
	//checks for all Ids
    while(1)
    {
    	//if there is space in the critical section
        if(sem->value > 0)
        {
        	//decrements accordingly
            sem->value--;
            return;
        }
        else
        {
            //delete tcb from readyQ
            tcb = DeleteQueue(RunQ);
            //add to semaphore queue
            AddQueue(sem->s_q, tcb);

            //if element NULL exit
            if(RunQ->element == NULL)
            {
                exit(0);
            }
            //swap current node with previous nodes
            swapcontext(&(sem->s_q->element->prev->context), &(RunQ->element->context));
        }
    }
}

//V semaphore
void V(semaphore *sem)
{
    struct TCB_t *tcb;
    //incrementing the value
    sem->value++;

	//checking if any threads are waiting in semaphore queue
    if(sem->s_q->element != NULL)
    {
    	//if yes delete from semaphore queue and add to readyQ
        tcb = DeleteQueue(sem->s_q);
        AddQueue(RunQ, tcb);
    }
}
