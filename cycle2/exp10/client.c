#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8080
#define MAXLINE 1024
#define SA struct sockaddr

void main()
{
 int sockfd,len,n;
 struct sockaddr_in servaddr;
 char *req="Client requested for time",buffer[MAXLINE];
 char *ack="Message recieved by client";
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
 len=sizeof(servaddr);
 sendto(sockfd,(const char*)req,strlen(req),
	MSG_CONFIRM,(const SA*)&servaddr,len);
 printf("Time request send to server...\n");
 n=recvfrom(sockfd,(char *)buffer,MAXLINE,
	    MSG_WAITALL,(SA*)&servaddr,&len);
 buffer[n]='\0';
 printf("Server : %s",buffer);
 sendto(sockfd,(const char*)ack,strlen(ack),
	MSG_CONFIRM,(const SA*)&servaddr,len);
 close(sockfd);
}
