#include<stdio.h>
#include<unistd.h>

void main()
{
 int fd[2],i,returnstatus;
 char writemessage[2][20]={"Hi All","Hello World"};
 char readmessage[20];
 returnstatus=pipe(fd);
 int pr=fork();
 if(returnstatus==-1)
 printf("Unable to create pipe...\n");
 else
 if(pr==0)
 for(i=0;i<2;i++)
 {
  printf("Child writing to pipe : %s\n",writemessage[i]);
  write(fd[1],writemessage[i],sizeof(writemessage[i]));
 }
 else
 for(i=0;i<2;i++)
 {
  read(fd[0],readmessage,sizeof(readmessage));
  printf("Parent reading from pipe : %s\n",readmessage);
 }
}
