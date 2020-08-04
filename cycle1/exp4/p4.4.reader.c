#include<stdio.h>
#include<sys/shm.h>

void main()
{
 key_t key;
 int shmid;
 key=ftok("shmfile",65);
 shmid=shmget(key,1024,0666|IPC_CREAT);
 char *message=(char *)shmat(shmid,(void *)0,0);
 printf("Data recieved : %s\n",message);
 shmdt(message);
 shmctl(shmid,IPC_RMID,NULL);
}
