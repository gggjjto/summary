#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define N 5

sem_t queue,busy,mutex;

int cnt=0,a=5,b=5;
int r[N]={0,1,2,3,4};

void sleep1()
{
  usleep((rand()%10+1)*100000);
}


void Reader(void *arg)
{
  int i=*(int*)arg;
  while(a>0)
  {
    a--;
    sleep1();
    sem_wait(&queue);
    sem_wait(&mutex);
    cnt++;
    if(cnt==1)
    {
      sem_wait(&busy);
    }
    sem_post(&mutex);
    sem_post(&queue);

    printf("Reader %d is reading !\n",i);
    printf("Reader %d reads end! \n",i);

    sem_wait(&mutex);
    cnt--;
    if(cnt==0)
    {
      sem_post(&busy);
    }
    sem_post(&mutex);
  }
}


void Writer()
{
  while(b>0)
  {
    b--;
    sleep1();
    sem_wait(&queue);
    sem_wait(&busy);

    printf("writer is weiting !\n");
    printf("writer writes end!\n");

    sem_post(&busy);
    sem_post(&queue);
  }
}


int main()
{
  int i;
  pthread_t writer,reader[N];
  srand((unsigned int)time(NULL) );
  sem_init(&queue,0,1);
  sem_init(&busy,0,1);
  sem_init(&mutex,0,1);

  for(i=0;i<5;i++){
    pthread_create(&reader[i],NULL,(void *)Reader,&r[i]);
  }
  pthread_create(&writer,NULL,(void *)Writer,NULL);
  
  pthread_join(writer,NULL);

  sem_destroy(&queue);
  sem_destroy(&busy);
  sem_destroy(&mutex);

  return 0;
}
