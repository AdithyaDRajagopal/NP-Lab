#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/sendfile.h>
#include<fcntl.h>
#define PORT 8080
#define SA struct sockaddr

int fsize(char *filename)
{
 FILE* fp=fopen(filename,"r");
 fseek(fp,0,2);
 int size=ftell(fp);
 return size;
}

void Xender(int sockfd)
{
 int pid;
 char file[80],response[80],ack[10];
 char fail[3],success[4];
 strcpy(fail,"NO");
 strcpy(success,"YES");
 read(sockfd,file,sizeof(file));
 printf("Client requested for the file : %s\n",file);
 if(access(file,F_OK)==-1)
 write(sockfd,fail,sizeof(fail));
 else
 {
  write(sockfd,success,sizeof(success));
  int fd,filesize;
  fd=open(file,O_RDONLY);
  filesize=fsize(file);
  write(sockfd,&filesize,sizeof(int));
  sendfile(sockfd,fd,NULL,filesize);
  printf("File sent to the client...\n");
  read(sockfd,ack,sizeof(ack));
 }
 pid=getpid();
 sprintf(response,"%d",pid);
 write(sockfd,response,sizeof(response));
 printf("PID sent to the client...\n");
}

void main()
{
 int sockfd,connfd,bindfd,len;
 struct sockaddr_in servaddr,cliaddr; 
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 if(sockfd<0)
 {
  printf("Socket creation failed...\n");
  exit(0);
 }
 else
 printf("Socket created successfully...\n");
 bzero(&servaddr,sizeof(servaddr));
 bzero(&cliaddr,sizeof(cliaddr));
 servaddr.sin_family=AF_INET;
 servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
 servaddr.sin_port=htons(PORT);
 bindfd=bind(sockfd,(SA*)&servaddr,sizeof(servaddr));
 if(bindfd<0)
 {
  printf("Socket bind failed...\n");
  exit(0);
 }
 else
 printf("Socket binded successfully...\n");
 listen(sockfd,3);
 printf("Server listening...\n");
 len=sizeof(cliaddr);
 connfd=accept(sockfd,(SA*)&cliaddr,&len);
 if(connfd<0)
 {
  printf("Server accept failed...\n");
  exit(0);
 }
 else
 printf("Server accepted the client...\n");
 Xender(connfd);
 close(sockfd);
}
