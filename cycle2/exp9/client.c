#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORT 8080
#define SA struct sockaddr
#define MAX 80

void main(int argc,char** argv)
{
 char *addr,buffer[MAX],n;
 int sockfd,connfd;
 struct sockaddr_in servaddr;
 if(argc<2)
 {
  printf("No address was passed...\n");
  exit(0);
 }
 addr=argv[1];
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 if(sockfd<0)
 {
  printf("Socket creation failed...\n");
  exit(0);
 }
 else
 printf("Socket successfully created...\n");
 memset(&servaddr,0,sizeof(servaddr));
 servaddr.sin_family=AF_INET;
 servaddr.sin_addr.s_addr=inet_addr(addr);
 servaddr.sin_port=htons(PORT);
 connfd=connect(sockfd,(SA*)&servaddr,sizeof(servaddr));
 if(connfd==0)
 printf("Connected to the server...\n");
 else
 {
  printf("Connection to the server failed...\n");
  exit(0);
 }
 while(1)
 {
  printf("Enter the message to server : ");
  fgets(buffer,MAX,stdin);
  sendto(sockfd,buffer,MAX,0,(SA*)&servaddr,sizeof(servaddr));
  if(strcmp(buffer,"exit\n")==0)
  {
   printf("Client exit...\n");
   break;
  }
  n=recvfrom(sockfd,buffer,MAX,0,NULL,NULL);
  buffer[n]='\0';
  printf("From server : %s",buffer);
 }
 close(sockfd);
}
