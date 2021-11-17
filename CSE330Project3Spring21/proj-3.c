#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sem.h"
int in = 0;
int out = 0;

int b = 0;
int c = 0;
int p = 0;
int n = 0;

int item = 0;
sem* fullSem; //consumer
sem* emptySem; //producer
sem* mutexSem;

int bufferArray[1000];

void producer(int pid, int n){

  while(pid < n){
    P(emptySem);
    printf("\n Producer %d is producing item number %d \n", pid, n);
    bufferArray[in] = item;
    item++;
    in = (in+1)%n;
    V(fullSem);
    pid++;
  }
  printf("\n Producer %d is waiting \n", pid);

}

void consumer(int cid,int n){

  while(cid < n){
    P(fullSem);
    item = bufferArray[out];
    out = (out+1);
    printf("\n Consumer %d is consuming item generated by Producer %d \n", cid, pid);
    V(emptySem);
    cid++;
  }
  printf("\n Consumer %d is waiting \n", cid);
}

int main(){
  scanf("%d,%d,%d,%d\n",&b,&p,&c,&n);

  RunQ = (struct q*)malloc(sizeof(q));
  InitQueue(RunQ);

  fullSem = initSem(0);
  emptySem = initSem(b);
  mutexSem = initSem(1);

  Run();

  return 0;
}
