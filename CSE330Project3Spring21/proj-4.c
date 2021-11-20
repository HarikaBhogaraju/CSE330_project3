#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sem.h"

semaphore* readerSem; //reader
semaphore* writerSem; //writer
//semaphore* mutexSem;

int i = 0; //global variable

int num = 0;
int r = 0;
int w = 0;

int readers = 0; //rc
int writers = 0; //wc
int readersWaiting = 0; //rwc
int writersWaiting = 0; //wwc

void readerEnrty(){
  printf("reader entry called\n");
  //reader entry

  //P(mutexSem);
  if(writersWaiting > 0 || writers > 0){
    readersWaiting++;
    //V(mutexSem);
    P(readerSem);
    //P(mutexSem);
    readersWaiting--;
  }
  readers++;
  if(readersWaiting > 0){
    V(readerSem);
  }
}
void readerExit(){
  printf("reader exit called\n");
  readers--;
  if(readers == 0 && writersWaiting > 0){
    V(writerSem);
  }
}
void Reader(int readerID){

  printf("reader called\n");
  readerEnrty();

  //printing
  printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, i );

  yield();

  printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, i );

  //reader exit
  //P(mutexSem);
  readerExit();

  struct TCB_T* tcbItem;
  tcbItem = DeleteQueue(RunQ);
  if(RunQ->element == NULL){
    exit(0);
  }
  swapcontext(&(tcbItem->context), &(RunQ->element->context));

}
void writerEntry(){
  printf("writer entry called\n");
  //P(mutexSem);
  if(readers > 0 || writers > 0 || readersWaiting > 0 || writersWaiting > 0){
    writersWaiting++;
    //V(mutexSem);
    P(writerSem);
    writersWaiting--;
  }
  writers++;
  printf("writer entry done\n");
}
void writerExit(){
  printf("writer exit called\n");
  //P(mutexSem);
  writers--;
  if(readersWaiting > 0){
    for(int j = 0 ;j<readersWaiting;j++){
      V(readerSem);
    }
  }
  else if(writersWaiting > 0){
    V(writerSem);
  }

}
void Writer(int writerID){
  printf("writer called\n");
  int x = 0;

  //writer entry
  writerEntry();
  //V(mutexSem);

  i = -writerID;
  x = -writerID;
  //printing
  printf("\n This is the %d th writer writing value i = %d \n", -writerID, i );

  yield();

  if(i == x){
    printf("\n This is the %d th writer verifying value i = %d \n", -writerID, i );
  }

  //writer exit
  writerExit();

  struct TCB_T* tcbItem;
  tcbItem = DeleteQueue(RunQ);
  if(RunQ->element == NULL){
    exit(0);
  }
  swapcontext(&(tcbItem->context), &(RunQ->element->context));

}

int main(int argc, char const *argv[]) {

  scanf("%d,%d",&r,&w);
  RunQ = (struct q*)malloc(sizeof(q));
  InitQueue(RunQ);

  readerSem = (struct semaphore*) malloc(sizeof(struct semaphore));
  initSem(readerSem,0);
  writerSem = (struct semaphore*) malloc(sizeof(struct semaphore));
  initSem(writerSem, 0);
  //mutexSem = initSem(1);

  for(int j = 0;j < (r+w);j++){
    scanf("%d",&num);
    //printf("Num = %d\n",num);
    if(num > 0){
      startThread(&Reader,num);
    }
    else{
      startThread(&Writer,num);
    }
  }
  run();
  return 0;
}


/*-----
//Yash shelar
//yshelar@asu.edu
//ASU ID: 1217410363

//including standard libraries
#include<stdio.h>
#include<stdlib.h>
//including threads.h to change access or make queue of TCBs
#include "semaphore.h"


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

//to help print and determine if producer should produce or wait
void reader(int readerID)
{

	readerEntry(readerID);

	printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, i);
	yield();

	printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, i);

	readerExit(readerID);

	//deleting the thread if from RunQ
    struct TCB_T *tcbItem = DeleteQueue(RunQ);

	//if element Null exit
    if(RunQ->element == NULL)
    {
        exit(0);
    }
    //else swapping context
    swapcontext(&(tcbItem->context), &(RunQ->element->context));
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

    //deleting the thread if from RunQ
    struct TCB_T *tcbItem = DeleteQueue(RunQ);

	//if element Null exit
    if(RunQ->element == NULL)
    {
        exit(0);
    }
    //else swapping context
    swapcontext(&(tcbItem->context), &(RunQ->element->context));
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

	//allocating memory for RunQ
    RunQ = (struct q*) malloc(sizeof(struct q));
    //semaphore for Consumer
    forReader = (struct semaphore*) malloc(sizeof(struct semaphore));
    //semaphore for producer
    forWriter = (struct semaphore*) malloc(sizeof(struct semaphore));

	//initializing RunQ
    InitQueue(RunQ);
    //initializing consumer and producer semaphore
    initSem(forReader, 0);
    initSem(forWriter, 0);

	int j = 0;
	//for running till the threads in RunQ
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
            startThread(&reader, id);
        }
        else
        {
        	//call consumer
            startThread(&writer, id);
        }
        //incrementing
        j++;
    }
    run();

	return 0;
}
--*/
