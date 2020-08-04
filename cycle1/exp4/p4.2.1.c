#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>

void main()
{
 char *myfifo="/tmp/myfifo";
 int fd;
 mkfifo(myfifo,0666);
 char str1[80],str2[80];
 while(1)
 {
  fd=open(myfifo,O_WRONLY);
  printf("Enter message for User 2: ");
  fgets(str2,80,stdin);
  write(fd,str2,sizeof(str2));
  close(fd);
  fd=open(myfifo,O_RDONLY);
  read(fd,str1,sizeof(str1));
  printf("User 2 : %s",str1);
  close(fd);
  if(strcmp(str2,"exit\n")==0||strcmp(str1,"exit\n")==0)
  break;
 }
}
