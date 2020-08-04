#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

int counter=0;
pthread_mutex_t rmutex;
sem_t resource;
int readcount=0;

void *reader(void *rno)
{
 int *readerid=(int *)rno;
 pthread_mutex_lock(&rmutex);
 readcount++;
 if(readcount==1)
 sem_wait(&resource);
 pthread_mutex_unlock(&rmutex);
 printf("Reader %d : read counter as %d\n",*readerid,counter);
 sleep(1);
 pthread_mutex_lock(&rmutex);
 readcount--;
 if(readcount==0)
 sem_post(&resource);
 pthread_mutex_unlock(&rmutex);
}

void *writer(void *wno)
{
 int *writerid=(int *)wno;
 sem_wait(&resource);
 counter++;
 printf("Writer %d : modified counter as %d\n",*writerid,counter);
 sem_post(&resource);
}

void main()
{
 pthread_t read[10],write[5];
 pthread_mutex_init(&rmutex,NULL);
 sem_init(&resource,0,1);
 int i,a[10]={1,2,3,4,5,6,7,8,9,10};
 for(i=0;i<5;i++)
 pthread_create(&write[i],NULL,(void *)writer,(void *)&a[i]);
 for(i=0;i<10;i++)
 pthread_create(&read[i],NULL,(void *)reader,(void *)&a[i]);
 for(i=0;i<5;i++)
 pthread_join(write[i],NULL);
 for(i=0;i<10;i++)
 pthread_join(read[i],NULL);
 pthread_mutex_destroy(&rmutex);
 sem_destroy(&resource);
}
