#include<stdio.h>
#include<stdlib.h>
//including threads.h to change access or make queue of TCBs
#include "threads.h"

//global variables to help

int i = 0;

int readCount = 0;
int writeCount = 0;
int readerWaitCount = 0;
int writerWaitCount = 0;

int numberOfReaders = 0;
int numberOfWriters = 0;

//both structs to call semaphores
struct semaphore *forReader;
struct semaphore *forWriter;


//struct type for semaphore data structure
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

            //if head NULL exit
            if(RunQ->head == NULL)
            {
                exit(0);
            }
            //swap current node with previous nodes
            swapcontext(&(sem->s_q->head->prev->context), &(RunQ->head->context));
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
    if(sem->s_q->head != NULL)
    {
    	//if yes delete from semaphore queue and add to readyQ
        tcb = DeleteQueue(sem->s_q);
        AddQueue(RunQ, tcb);
    }
}

//to help print and determine if producer should produce or wait
void reader(int readerID)
{

	readerEntry(readerID);

	printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, i);
	yield();

	printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, i);

	readerExit(readerID);

	//deleting the thread if from readyQ
    struct TCB_t *tcb = DeleteQueue(RunQ);

	//if head Null exit
    if(RunQ->head == NULL)
    {
        exit(0);
    }
    //else swapping context
    swapcontext(&(tcb->context), &(RunQ->head->context));
}

//to help print and bdetermine if consumer can consume
void writer(int writerID)
{
	int help = 0;

	writerEntry(writerID);
	i = -writerID;
	help = -writerID;

	printf("\n This is the %d th writer writing value i = %d \n", -writerID, i);
	yield();

	if((-writerID) == help)
	{
		printf("\n This is the %d th writer verifying value i = %d \n", -writerID, i);
	}

	writerExit(writerID);

    //deleting the thread if from readyQ
    struct TCB_t *tcb = DeleteQueue(RunQ);

	//if head Null exit
    if(RunQ->head == NULL)
    {
        exit(0);
    }
    //else swapping context
    swapcontext(&(tcb->context), &(RunQ->head->context));
}

void readerEntry(int ID)
{
	if(writerWaitCount > 0 || writeCount > 0)
	{
		readerWaitCount++;
		P(forReader);
		readerWaitCount--;
	}
	readCount++;
	if(readerWaitCount > 0)
	{
		V(forReader);
	}
}

void readerExit(int ID)
{
	readCount--;
	if(readCount == 0 && writerWaitCount > 0)
	{
		V(forWriter);
	}
}

void writerEntry(int ID)
{
	if(readCount > 0 || writeCount > 0 || readerWaitCount > 0 || writerWaitCount > 0)
	{
		writerWaitCount++;
		P(forWriter);
		writerWaitCount--;
	}
	writeCount++;
}

void writerExit(int ID)
{
	writeCount--;
	if(readerWaitCount > 0)
	{
		for(int k = 0; k < readerWaitCount; k++)
		{
			V(forReader);
		}
	}
	else if(writerWaitCount > 0)
	{
		V(forWriter);
	}
}

//main function
int main() {
	//taking inputs
	scanf("%d,%d",&numberOfReaders, &numberOfWriters);

	//allocating memory for readyQ
    RunQ = (struct q*) malloc(sizeof(struct q));
    //Semaphore for Consumer
    forReader = (struct semaphore*) malloc(sizeof(struct semaphore));
    //Semaphore for producer
    forWriter = (struct semaphore*) malloc(sizeof(struct semaphore));

	//initializing RunQ
    InitQueue(RunQ);
    //initializing consumer and producer semaphore
    initSem(forReader, 0);
    initSem(forWriter, 0);

	int j = 0;
	//for running till the threads in readyQ
    int stop = numberOfReaders + numberOfWriters;
    while(j < stop)
    {
    	//scanning the thread id
    	int id;
    	scanf("%d", &id);

    	//if positive
       	if(id > 0)
        {
        	//call producer
            start_thread(&reader, id);
        }
        else
        {
        	//call consumer
            start_thread(&writer, id);
        }
        //incrementing
        j++;
    }
    run();

	return 0;
}
