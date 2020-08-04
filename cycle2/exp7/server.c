#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd)
{
 char buff[MAX];
 while(1)
 {
  bzero(buff,sizeof(buff));
  read(sockfd,buff,sizeof(buff));
  printf("From client : %s",buff);
  if(strcmp(buff,"exit\n")==0)
  {
   printf("Client exited...\n");
   break;
  }
  bzero(buff,sizeof(buff));
  printf("\tTo client : ");
  fgets(buff,MAX,stdin);
  write(sockfd,buff,sizeof(buff));
  if(strcmp(buff,"exit\n")==0)
  {
   printf("Server exit...\n");
   break;
  }
 }
}

void main()
{
 int sockfd,connfd,bindfd,len;
 struct sockaddr_in servaddr,cliaddr;
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 if(sockfd==-1)
 {
  printf("Socket creation failed...\n");
  exit(0);
 }
 else
 printf("Socket created successfully...\n");
 bzero(&servaddr,sizeof(servaddr));
 servaddr.sin_family=AF_INET;
 servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
 servaddr.sin_port=htons(PORT);
 bindfd=bind(sockfd,(SA*)&servaddr,sizeof(servaddr));
 if(bindfd==0)
 printf("Socket successfully binded...\n");
 else
 {
  printf("Socket bind failed...\n");
  exit(0);
 }
 if(listen(sockfd,5)!=0)
 {
  printf("Listen failed...\n");
  exit(0);
 }
 else
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
 func(connfd);
 close(sockfd);
}
