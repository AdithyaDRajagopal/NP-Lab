#include<stdio.h>
#include<pthread.h>

void* ThreadFun(void *args)
{
 int *id=(int *)args;
 printf("Inside thread %d\n",*id);
 return NULL;
}

void main()
{
 pthread_t id;
 int ret,i,n;
 printf("Enter the number of threads:");
 scanf("%d",&n);
 for(i=1;i<=n;i++)
 {
  ret=pthread_create(&id,NULL,&ThreadFun,(void *)&i);
  if(ret==0)
  printf("Thread %d created successfully...\n",i);
  else
  printf("Thread %d not created.\n",i);
  pthread_join(id,NULL);
  printf("Outside thread %d\n",i);
 }
}
