#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#define PORT 5000
#define MAXLINE 1024
#define SA struct sockaddr

void main()
{
 int sockfd,n,len;
 char msg[80],buff[MAXLINE];
 struct sockaddr_in servaddr;
 sockfd=socket(AF_INET,SOCK_DGRAM,0);
 if(sockfd<0)
 {
  printf("Socket creation failed...\n");
  exit(0);
 }
 else
 printf("Socket successfully created...\n");
 memset(&servaddr,0,sizeof(servaddr));
 servaddr.sin_family=AF_INET;
 servaddr.sin_port=htons(PORT);
 servaddr.sin_addr.s_addr=INADDR_ANY;
 printf("Enter the message for the server : ");
 fgets(msg,80,stdin);
 len=sizeof(servaddr);
 sendto(sockfd,(const char*)msg,strlen(msg),
	MSG_CONFIRM,(const SA*)&servaddr,len);
 printf("Message Sent...\n");
 n=recvfrom(sockfd,(char *)buff,MAXLINE,
	    MSG_WAITALL,(SA*)&servaddr,&len);
 buff[n]='\0';
 printf("Server : %s",buff);
 close(sockfd);
}
