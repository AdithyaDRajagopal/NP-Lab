#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void main()
{
 int x;
 x=fork();
 if(x==0)
 printf("Child Process Executing...\n");
 else
 {
  printf("Parent Process Executing...\n");
  wait(NULL);
  printf("Exiting Child Process...\n");
 }
 printf("Exiting...\n");
 exit(0);
 printf("Hello World\n");
}
