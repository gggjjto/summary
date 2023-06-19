#include<stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>

#define N 5

int count=0,a=5,b=5;
int r[N]={0,1,2,3,4};
sem_t wmutex,rmutex;

void sleep1()
{
  usleep((rand()%10 + 1)*100000);
}

void Reader(void * arg)
{
  int i=*(int *)arg;
  while(a>0)
  {
    a--;
    sleep1();
    sem_wait(&rmutex);
    if(count==0){
      sem_wait(&wmutex);
    }
    count++;
    sem_post(&rmutex);
    
    printf("Reander %d is reanding! \n",i);
    printf("Rander %d reands end ! \n",i);
    
    sem_wait(&rmutex);
    count--;
    if(count==0){
      sem_post(&wmutex);
    }
    sem_post(&rmutex);
  }
}

void Writer()
{
  while(b>0){
    b--;
    sleep1();
    sem_wait(&rmutex);
    printf("Writer is Writing ! \n");
    printf("Writer writes end ! \n");
    sem_post(&rmutex);
  }
}



int main()
{
  int i;
  pthread_t writer,reader[N];
  srand((unsigned int)time(NULL));

  sem_init(&wmutex,0,1);
  sem_init(&rmutex,0,1);

  for(i=0;i<5;i++){
    pthread_create(&reader[i],NULL,(void*)Reader,&r[i]);
  }

  pthread_create(&writer,NULL,(void *)Writer,NULL);

  pthread_join(writer,NULL);

  sem_destroy(&rmutex);
  sem_destroy(&wmutex);

  return 0;
  
}
