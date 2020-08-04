#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

void main()
{
 int ip=open("input.txt",O_RDONLY|O_CREAT);
 int op=open("output.txt",O_WRONLY|O_CREAT|O_TRUNC,0644);
 int sz;
 printf("fd=%d\n",ip);
 if(ip==-1)
 printf("File cannot be opened...\n");
 else
 {
  char *c=(char *)calloc(100,sizeof(char));
  sz=read(ip,c,10);
  c[sz]='\n';
  sz=write(op,c,11);
  if(close(ip)==0&&close(op)==0)
  printf("Files closed...\n");
 }
}
