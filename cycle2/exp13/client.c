#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>
#define MAX 1024
#define PORT 8080
#define SA struct sockaddr

void sendMail(char* from,char* to,char* body)
{
 char buffer[MAX],msg[MAX];
 int sockfd,connfd;
 struct sockaddr_in servaddr;
 memset(buffer,' ',MAX);
 char data[MAX],response[MAX],command[MAX];
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 if(sockfd<0)
 {
  printf("Socket creation failed...\n");
  exit(0);
 }
 else
 printf("Socket created successfully...\n");
 servaddr.sin_family=AF_INET;
 servaddr.sin_port=htons(PORT);
 servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
 connfd=connect(sockfd,(SA*)&servaddr,sizeof(servaddr));
 if(connfd<0)
 {
  printf("Conection to the server failed...\n");
  exit(0);
 }
 read(sockfd,buffer,MAX);
 if(strncmp("220",buffer,3)==0)
 printf("Connected to the SMTP server...\n");
 else
 {
  printf("Unable to connect to the server...\n");
  exit(0);
 }
 sprintf(msg,"HELO mail.com");
 write(sockfd,msg,sizeof(msg));
 memset(buffer,' ',MAX);
 read(sockfd,buffer,MAX);
 if(strncmp("250",buffer,3)==0)
 printf("HELO successful...\n");
 else if(strncmp("503",buffer,3)==0)
 {
  printf("Bad sequence of commands...\n");
  exit(0);
 }
 else if(strncmp("501",buffer,3)==0)
 {
  printf("Invalid domain...\n");
  exit(0);
 }
 strcpy(command,"MAIL FROM:<");
 strcat(command,from);
 strcat(command,">");
 write(sockfd,command,sizeof(command));
 memset(buffer,' ',MAX);
 read(sockfd,buffer,MAX);
 if(strncmp("250",buffer,3)==0)
 printf("Mail successful...\n");
 else if(strncmp("503",buffer,3)==0)
 {
  printf("Bad sequence of commands...\n");
  exit(0);
 }
 else if(strncmp("501",buffer,3)==0)
 {
  printf("Check sender...\n");
  exit(0);
 }
 strcpy(command,"RCPT TO:<");
 strcat(command,to);
 strcat(command,">");
 write(sockfd,command,sizeof(command));
 memset(buffer,' ',MAX);
 read(sockfd,buffer,MAX);
 if(strncmp("250",buffer,3)==0)
 printf("RCPT TO successful...\n");
 else if(strncmp("503",buffer,3)==0)
 {
  printf("Bad sequence of commands...\n");
  exit(0);
 }
 else if(strncmp("501",buffer,3)==0)
 {
  printf("Check reciever...\n");
  exit(0);
 }
 strcpy(command,"DATA\n");
 write(sockfd,command,sizeof(command));
 memset(buffer,' ',MAX);
 read(sockfd,buffer,MAX);
 if(strncmp("354",buffer,3)==0)
 {
  strcat(body,"<CRLF>");
  write(sockfd,body,strlen(body));
  printf("%s",body);
  printf("Data sent to server...\n");
 }
 strcpy(command,"QUIT");
 write(sockfd,command,sizeof(command));
 memset(buffer,' ',MAX);
 read(sockfd,buffer,MAX);
 if(strncmp("221",buffer,3)==0)
 printf("Connection closed with server...\n");
 close(sockfd);
}

void main() 
{
 char from[80],to[80],data[MAX];
 printf("Enter from mail address : ");
 fgets(from,80,stdin);
 printf("Enter to mail address : ");
 fgets(to,80,stdin);
 printf("Enter mail body : \n");
 fgets(data,MAX,stdin);
 sendMail(from,to,data);
}