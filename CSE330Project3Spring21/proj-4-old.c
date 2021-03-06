#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sem.h"

sem* readerSem; //reader
sem* writerSem; //writer
//sem* mutexSem;

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

  readerSem = (struct sem*) malloc(sizeof(struct sem));
  initSem(readerSem,0);
  writerSem = (struct sem*) malloc(sizeof(struct sem));
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
