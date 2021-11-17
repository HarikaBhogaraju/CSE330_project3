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
sem* fullSem;
sem* emptySem;
sem* mutexSem;

int bufferArray[b];

void producer(){
  int pid = 0;
  while(pid < n){
    P(emptySem);
    bufferArray[in] = item;
    item++;
    in = (in+1)%n;
    V(fullSem);
    pid++;
  }

}

void consumer(){
  int cid = 0;
  while(cid < n){
    P(fullSem);
    item = bufferArray[out];
    out = (out+1)%n;
    V(emptySem);
    cid++;
  }


}

int main(){
  scanf("%d,%d,%d,%d\n",&b,&p,&c,&n);

  RunQ = (struct q*)malloc(sizeof(q));
  InitQueue(RunQ);

  fullSem = initSem(0);
  emptySem = initSem(n);
  mutexSem = initSem(1);

  bufferArray = malloc(b* sizeof(int));

  return 0;
}
