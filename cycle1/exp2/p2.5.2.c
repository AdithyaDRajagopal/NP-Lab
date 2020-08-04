#include<stdio.h>
#include<sys/shm.h>

void main()
{
 key_t key;
 int shmid;
 key=ftok("shmfile",65);
 shmid=shmget(key,1024,0666|IPC_CREAT);
 printf("Shared Memory ID : %d\n",shmid);
 char *message=(char *)shmat(shmid,(void *)0,0);
 printf("Write Data : ");
 scanf("%[^\n]",message);
 printf("Data written into shared memory : %s\n",message);
 shmdt(message);
}
