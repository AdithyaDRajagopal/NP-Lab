#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
int flag=2;

void handle(int sig)
{
 printf("Alarm signal %d sent...\n",3-flag);
 flag--;
 alarm(1);
}

void main()
{
 pid_t pid;
 pid=getpid();
 printf("Process ID: %d\n",pid);
 signal(SIGALRM,handle);
 alarm(1);
 while(flag)
 sleep(1);
}
