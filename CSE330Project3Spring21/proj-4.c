#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sem.h"

sem* readerSem; //reader
sem* writerSem; //writer
sem* mutexSem;

int i = 0; //global variable

int num = 0;

int r = 0;
int w = 0;

int readers = 0;
int writers = 0;

int readersWaiting = 0;
int writersWaiting = 0;

void Reader(int readerID){

  //reader entry

  //P(mutex);
  if(writersWaiting > 0 || writers > 0){
    readersWaiting++;
    //V(mutex);
    P(readerSem);
    //P(mutex);
    readersWaiting--;
  }
  readers++;
  if(readersWaiting > 0){
    V(readerSem);
  }
  else{
    //V(mutex);
  }

  //printing
  printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, i );


  //reader exit
  //P(mutex);
  readers--;
  if(readers == 0 && writersWaiting > 0){
    V(writerSem);
  }
  else{
    //V(mutex);
  }

  printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, i );
}
void Writer(int writerID){
  i++;
  //writer entry
  //P(mutex);
  if(readers > 0 || writers > 0){
    writersWaiting++;
    //V(mutex);
    P(writerSem);
    writersWaiting--;
  }
  writersWaiting++;
  //V(mutex);

  //printing
  printf("\n This is the %d th writer writing value i = %d \n", -writerID, i );


  //writer exit
  //P(mutex);
  writers--;
  if(readersWaiting > 0){
    for(int i = 1;i<readersWaiting;i++){
      V(readerSem);
    }
  }
  else if(writersWaiting > 0){
    V(writerSem);
  }
  else{
    //V(mutex);
  }
  printf("\n This is the %d th writer verifying value i = %d \n", writerID, i );

}

int main(int argc, char const *argv[]) {
  scanf("%d,%d\n",&r,&w);
  RunQ = (struct q*)malloc(sizeof(q));
  InitQueue(RunQ);
  readerSem = initSem(0);
  writerSem = initSem(0);
  mutexSem = initSem(1);

  for(int i = 0;i < r+w;i++){
    scanf("%d\n",&num);
    if(num > 0){
      r = Reader(num);
      startThread(r);
    }
    else{
      w = Writer(num);
      startThread(w);
    }
  }



  return 0;
}
