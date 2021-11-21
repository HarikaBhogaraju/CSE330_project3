#include<stdio.h>
#include<stdlib.h>
#include "sem.h"


int i = 0;

int readCount = 0;
int writeCount = 0;
int readerWaitCount = 0;
int writerWaitCount = 0;

int numberOfReaders = 0;
int numberOfWriters = 0;

struct semaphore *readerSem;
struct semaphore *writerSem;




void reader(int readerID)
{

	readerEntry(readerID);

	printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, i);
	yield();

	printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, i);

	readerExit(readerID);


    struct TCB_t *tcb = DeleteQueue(RunQ);

    if(RunQ->element == NULL)
    {
        exit(0);
    }

    swapcontext(&(tcb->context), &(RunQ->element->context));
}

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


    struct TCB_t *tcb = DeleteQueue(RunQ);


    if(RunQ->element == NULL)
    {
        exit(0);
    }

    swapcontext(&(tcb->context), &(RunQ->element->context));
}

void readerEntry(int ID)
{
	if(writerWaitCount > 0 || writeCount > 0)
	{
		readerWaitCount++;
		P(readerSem);
		readerWaitCount--;
	}
	readCount++;
	if(readerWaitCount > 0)
	{
		V(readerSem);
	}
}

void readerExit(int ID)
{
	readCount--;
	if(readCount == 0 && writerWaitCount > 0)
	{
		V(writerSem);
	}
}

void writerEntry(int ID)
{
	if(readCount > 0 || writeCount > 0 || readerWaitCount > 0 || writerWaitCount > 0)
	{
		writerWaitCount++;
		P(writerSem);
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
			V(readerSem);
		}
	}
	else if(writerWaitCount > 0)
	{
		V(writerSem);
	}
}


int main() {

	scanf("%d,%d",&numberOfReaders, &numberOfWriters);

    RunQ = (struct q*) malloc(sizeof(struct q));


    writerSem = (struct semaphore*) malloc(sizeof(struct semaphore));


    InitQueue(RunQ);

    initSem(readerSem, 0);
    initSem(writerSem, 0);

	int j = 0;

    int stop = numberOfReaders + numberOfWriters;
    while(j < stop)
    {

    	int id;
    	scanf("%d", &id);


       	if(id > 0)
        {

            start_thread(&reader, id);
        }
        else
        {

            start_thread(&writer, id);
        }

        j++;
    }
    run();

	return 0;
}
