#include <stdio.h>
#include<pthread.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

sem_t chopstick[5];
sem_t mutex;

int r[5]={0,1,2,3,4};


void sleep1()
{
  usleep((rand()%10+1)*100000);
}


void Pi(void *arg){
  int i=*(int *)arg;
  while(1)
  {

    sleep1();
    sem_wait(&mutex);
    sem_wait(&chopstick[i]);
    sem_wait(&chopstick[(i+1)%5]);
    sem_post(&mutex);
    
    printf("%d The philosopher is eating\n",i);

    sem_post(&chopstick[i]);
    sem_post(&chopstick[(i+1)%5]);
    
    printf("philosophers are thinking \n");

  }
}


int main()
{
  int i;
  pthread_t P[5];
  
  srand((unsigned int)time(NULL));
  sem_init(&mutex,0,1);

  for(i=0;i<5;i++)
  {
    sem_init(&chopstick[i],0,1);
    pthread_create(&P[i],NULL,(void *)Pi,&r[i]);
  }
  
  for(i=0;i<5;i++)
  {
    pthread_join(P[i],NULL);
  }

  sem_destroy(&mutex);
  for(i=0;i<5;i++){
    sem_destroy(&chopstick[i]);
  }

}
