#include<stdio.h>
#include<sys/msg.h>

void main()
{
 key_t key;
 int msgid;
 char message[80];
 key=ftok("progfile",65);
 msgid=msgget(key,0666|IPC_CREAT);
 msgrcv(msgid,&message,sizeof(message),0,0);
 printf("Data recieved : %s\n",message);
 msgctl(msgid,IPC_RMID,NULL);
}
