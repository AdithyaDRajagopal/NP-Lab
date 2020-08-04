#include<stdio.h>
#include<sys/msg.h>

void main()
{
 key_t key;
 int msgid;
 char message[80];
 key=ftok("progfile",65);
 msgid=msgget(key,0666|IPC_CREAT);
 printf("Write Data : ");
 scanf("%[^\n]",message);
 msgsnd(msgid,&message,sizeof(message),0);
 printf("Data written into message queue : %s\n",message);
}
