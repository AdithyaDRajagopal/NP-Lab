#include<stdio.h>
#include<unistd.h>

void main()
{
 int fd[2],i,returnstatus;
 char writemessage[2][20]={"Hi All","Hello World"};
 char readmessage[20];
 returnstatus=pipe(fd);
 if(returnstatus==-1)
 printf("Unable to create pipe...\n");
 else
 {
  for(i=0;i<2;i++)
  write(fd[1],writemessage[i],sizeof(writemessage[i]));
  for(i=0;i<2;i++)
  {
   read(fd[0],readmessage,sizeof(readmessage));
   printf("Message %d : %s\n",i+1,readmessage);
  }
 }
}
