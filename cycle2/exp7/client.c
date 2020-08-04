#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd)
{
 char buff[MAX];
 while(1)
 {
  bzero(buff,sizeof(buff));
  printf("Enter message to server : ");
  fgets(buff,MAX,stdin);
  write(sockfd,buff,sizeof(buff));
  if(strcmp(buff,"exit\n")==0)
  {
   printf("Client exit...\n");
   break;
  }
  bzero(buff,sizeof(buff));
  read(sockfd,buff,sizeof(buff));
  printf("\tFrom server : %s",buff);
  if(strcmp(buff,"exit\n")==0)
  {
   printf("Server exited...\n");
   break;
  }
 }
}

void main()
{
 int sockfd,connfd;
 struct sockaddr_in servaddr;
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 if(sockfd==-1)
 {
  printf("Socket creation failed...\n");
  exit(0);
 }
 else
 printf("Socket successfully created...\n");
 bzero(&servaddr,sizeof(servaddr));
 servaddr.sin_family=AF_INET;
 servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
 servaddr.sin_port=htons(PORT);
 connfd=connect(sockfd,(SA*)&servaddr,sizeof(servaddr));
 if(connfd==0)
 printf("Connected to the server...\n");
 else
 {
  printf("Connection with the server failed...\n");
  exit(0);
 }
 func(sockfd);
 close(sockfd);
}
