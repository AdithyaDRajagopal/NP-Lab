#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORT 5000
#define MAXLINE 1024
#define SA struct sockaddr

void main()
{
 int sockfd,bindfd,n,len;
 struct sockaddr_in servaddr,cliaddr;
 char buff[MAXLINE],msg[80];
 sockfd=socket(AF_INET,SOCK_DGRAM,0);
 if(sockfd<0)
 {
  printf("Socket creation failed...\n");
  exit(0);
 }
 else
 printf("Socket successfully created...\n");
 memset(&servaddr,0,sizeof(servaddr));
 memset(&cliaddr,0,sizeof(cliaddr));
 servaddr.sin_family=AF_INET;
 servaddr.sin_addr.s_addr=INADDR_ANY;
 servaddr.sin_port=htons(PORT);
 bindfd=bind(sockfd,(const SA*)&servaddr,sizeof(servaddr));
 if(bindfd<0)
 {
  printf("Socket bind failed...\n");
  exit(0);
 }
 else
 printf("Socket successfully binded...\n");
 len=sizeof(cliaddr);
 n=recvfrom(sockfd,(char *)buff,MAXLINE,
	    MSG_WAITALL,(SA*)&cliaddr,&len);
 buff[n]='\0';
 printf("Client : %s",buff);
 printf("Enter the message for the client : ");
 fgets(msg,sizeof(msg),stdin);
 sendto(sockfd,(const char *)msg,strlen(msg),
	MSG_CONFIRM,(const SA*)&cliaddr,len);
 printf("Message sent...\n");
 close(sockfd);
}
