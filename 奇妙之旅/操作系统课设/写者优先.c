#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>


#define N 5

int cnt=0,cnt1=0,a=5,b=2;
int r[5]={0,1,2,3,4};


sem_t Read,Write,ReaderMutex,WriterMutex;

void sleep1()
{
  usleep((rand()%10 +1 )*100000);
}

void Reader(void *arg)
{
  int i=*(int *)arg;
  while(a>0)
  {
    a--;
    //usleep(300);
    sleep1();
    sem_wait(&Read);
    sem_wait(&ReaderMutex);
    cnt++;
    if(cnt==1){
      sem_wait(&Write);
    }
    sem_post(&ReaderMutex);
    sem_post(&Read);
    
    printf("Rander %d is reading !\n",i);
    printf("Reader %d reads end ! \n",i);


    sem_wait(&ReaderMutex);
    cnt--;
    if(cnt==0){
      sem_post(&Write);
    }
    sem_post(&ReaderMutex);
  } 
}


void Writer(void *arg)
{
  int i=*(int *)arg;
  while(b>0){
    b--;
    //usleep(300);
    sleep1();
    sem_wait(&WriterMutex);
    cnt1++;
    if(cnt1==1){
      sem_wait(&Read);
    }
    sem_post(&WriterMutex);
    
    sem_wait(&Write);
    printf("Writer %d is Writing ! \n",i);
    printf("Writer %d writes end! \n",i);
    sem_post(&Write);

    sem_wait(&WriterMutex);
    cnt1--;
    if(cnt1==0){
      sem_post(&Read);
    }
    sem_post(&WriterMutex);
  }
}




int main()
{
  int i;
  pthread_t write[N],reader[N];
  srand((unsigned int ) time(NULL));
  sem_init(&Read,0,1);
  sem_init(&Write,0,1);
  sem_init(&ReaderMutex,0,1);
  sem_init(&WriterMutex,0,1);
    
  for(i=0;i<5;i++){
    pthread_create(&reader[i],NULL,(void *)Reader,&r[i]);
  }

  for(i=0;i<2;i++)
  {
    pthread_create(&write[i],NULL,(void *)Writer,&r[i]);
  }

  for(i=0;i<2;i++){
    pthread_join(write[i],NULL);
  }
  for(i=0;i<5;i++){
    pthread_join(reader[i],NULL);
  }

  sem_destroy(&Read);
  sem_destroy(&Write);
  sem_destroy(&ReaderMutex);
  sem_destroy(&WriterMutex);
  return 0;
}
