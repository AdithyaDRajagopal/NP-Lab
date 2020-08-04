#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#define PORT 8080
#define SA struct sockaddr

void main()
{
 int sockfd,connfd,filesize,fd;
 struct sockaddr_in servaddr;
 char *data,file[80],reply[80],ack[10];
 strcpy(ack,"Received");
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 if(sockfd<0)
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
 if(connfd<0)
 {
  printf("Connection to the server failed...\n");
  exit(0);
 }
 else
 printf("Connected to the server...\n");
 printf("Enter the name of the file to search for : ");
 scanf("%s",file);
 write(sockfd,file,sizeof(file));
 bzero(reply,sizeof(reply));
 read(sockfd,reply,sizeof(reply));
 if(strcmp(reply,"NO")==0)
 printf("File not found...\n");
 else
 {
  printf("File found...\n");
  printf("Enter the name of the file to store to : ");
  scanf("%s",file);
  read(sockfd,&filesize,sizeof(int));
  data=malloc(filesize);
  fd=open(file,O_CREAT|O_EXCL|O_WRONLY,0666);
  recv(sockfd,data,filesize,0);
  write(fd,data,filesize);
  printf("File successfully copied to %s...\n",file);
  write(sockfd,ack,sizeof(ack));
  close(fd);
 }
 bzero(reply,sizeof(reply));
 read(sockfd,reply,sizeof(reply));
 int pid=atoi(reply);
 printf("Process ID of server : %d\n",pid);
 close(sockfd);
}
