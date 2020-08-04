#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#define PORT 8080
#define SA struct sockaddr
#define MAX 80

void main()
{
 int sockfd,bindfd,connfd,len,n;
 struct sockaddr_in servaddr,cliaddr;
 char clientAddr[80],buffer[MAX];
 pid_t child;
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 if(sockfd<0)
 {
  printf("Socket creation failed...\n");
  exit(0);
 }
 else
 printf("Socket created successfully...\n");
 memset(&servaddr,0,sizeof(servaddr));
 servaddr.sin_family=AF_INET;
 servaddr.sin_addr.s_addr=INADDR_ANY;
 servaddr.sin_port=htons(PORT);
 bindfd=bind(sockfd,(SA*)&servaddr,sizeof(servaddr));
 if(bindfd<0)
 {
  printf("Socket bind failed...\n");
  exit(0);
 }
 else
 printf("Socket binded successfully...\n");
 listen(sockfd,5);
 while(1)
 {
  len=sizeof(cliaddr);
  connfd=accept(sockfd,(SA*)&cliaddr,&len);
  if(connfd<0)
  {
   printf("Error accpeting connection...\n");
   exit(0);
  }
  else
  printf("Connection accepted...\n");
  inet_ntop(AF_INET,&(cliaddr.sin_addr),clientAddr,80);
  if((child=fork())==0)
  {
   close(sockfd);
   while(1)
   {
    memset(buffer,0,MAX);
    n=recvfrom(connfd,buffer,MAX,0,(SA*)&cliaddr,&len);
    buffer[n]='\0';
    if(strcmp(buffer,"exit\n")==0)
    {
     n=-1;
     printf("Client %s exited...\n",clientAddr);
     break;
    }
    printf("Data recieved from %s : %s",clientAddr,buffer);
    printf("Enter the message to %s : ",clientAddr);
    fgets(buffer,MAX,stdin);
    sendto(connfd,buffer,MAX,0,(SA*)&cliaddr,len);
   }
  }
  close(connfd);
  if(n==-1)
  break;
 }
}
