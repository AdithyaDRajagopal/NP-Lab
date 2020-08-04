#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<time.h>
#define PORT 8080
#define MAXLINE 1024
#define SA struct sockaddr

void main()
{
 int sockfd,bindfd,len,n;
 struct sockaddr_in servaddr,cliaddr;
 char buffer[MAXLINE];
 time_t t;
 time(&t);
 char *time=ctime(&t);
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
 n=recvfrom(sockfd,(char *)buffer,MAXLINE,
	    MSG_WAITALL,(SA*)&cliaddr,&len);
 buffer[n]='\0';
 printf("%s\n",buffer);
 sendto(sockfd,(char *)time,MAXLINE,
	MSG_CONFIRM,(const SA*)&cliaddr,len);
 printf("Date and time sent to the client...\n");
 n=recvfrom(sockfd,(char *)buffer,MAXLINE,
	    MSG_WAITALL,(SA*)&cliaddr,&len);
 buffer[n]='\0';
 printf("%s\n",buffer);
 close(sockfd);
}
