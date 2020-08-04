#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>
#define SA struct sockaddr
#define PORT 8080
#define MAX 1024

char users[2][80]={"abc@mail.com","xyz@mail.com"};
char from[80],to[80];

int processMailFrom(char* buff)
{
 int i;
 char s[50];
 if(strncmp("MAIL FROM",buff,9)==0)
 {
  printf("MAIL FROM received...\n");
  for(i=0;i<strlen(buff);i++)
  {
   s[i]=buff[i+11];
   if(s[i]=='>')
   break;
  }
  s[i+1]='\0';
  for(i=0;i<2;i++)
  if(strncmp(users[i],s,strlen(users[i]))==0)
  {
   strcpy(from,users[i]);
   return 250;
  }
  return 501;
 }
 return 503;
}

int processRcptTo(char* buff)
{
 int i;
 char s[50];
 if(strncmp("RCPT TO",buff,7)==0)
 {
  printf("RCPT TO received...\n");
  for(i=0;i<strlen(buff);i++)
  {
   s[i]=buff[i+9];
   if(s[i]=='>')
   break;
  }
  for(i=0;i<2;i++)
  if(strncmp(users[i],s,strlen(users[i]))==0)
  {
   strcpy(to,users[i]);
   return 250;
  }
  return 501;
 }
 return 503;
}

void handleData(int sockfd)
{
 char buffer[MAX];
 char msg[80],str[MAX];
 int mail,i,j;
 strcpy(msg,to);
 strcat(msg,".txt");
 mail=open(msg,O_CREAT|O_EXCL|O_WRONLY,0666);
 strcpy(msg,"FROM : ");
 strcat(msg,from);
 strcat(msg,"\n");
 write(mail,msg,sizeof(msg));
 read(sockfd,buffer,sizeof(buffer));
 for(i=0;i<MAX;i++)
 {
  if(buffer[i]=='<')
  {
   char end[10]="<CRLF>\n";
   for(j=0;j<5;j++)
   if(buffer[i+j]!=end[j])
   break;
   if(j==5)
   break;
  }
 }
 int len=i+j+2;
 buffer[len-1]='\n';
 write(mail,buffer,len);
 printf("Mail content successfully written to file\n");
 close(mail);
} 

void processMail(int sockfd)
{
 char buffer[MAX],msg[MAX];
 int status=220;
 memset(buffer,' ',MAX);
 sprintf(msg,"%d mail.com Ready\n",status);
 write(sockfd,msg,sizeof(msg));
 read(sockfd,buffer,MAX);
 if(strncmp("HELO",buffer,4)==0)
 {
  printf("HELO received...\n");
  if(strncmp("HELO mail.com",buffer,13)==0)
  status=250;
  else
  status=501;
 }
 else
 {
  status=503;
  sprintf(msg,"%d bad sequence",status);
  write(sockfd,msg,sizeof(msg));
  close(sockfd);
  exit(0);
 }
 if(status==250)
 {
  printf("250 OK\n");
  sprintf(msg,"%d OK",status);
  write(sockfd,msg,sizeof(msg));
 }
 else if(status==501)
 {
  sprintf(msg,"%d wrong domain",status);
  write(sockfd,msg,sizeof(msg));
  close(sockfd);
  exit(0);
 }
 memset(buffer,' ',MAX);
 read(sockfd,buffer,sizeof(buffer));
 status=processMailFrom(buffer);
 if(status==250)
 {
  printf("250 OK\n");
  sprintf(msg,"%d OK",status);
  write(sockfd,msg,sizeof(msg));
 }
 else if(status==501)
 {
  sprintf(msg,"%d wrong domain",status);
  write(sockfd,msg,sizeof(msg));
  close(sockfd);
  exit(0);
 }
 else if(status==503)
 {
  sprintf(msg,"%d bad sequence",status);
  write(sockfd,msg,sizeof(msg));
  close(sockfd);
  exit(0);
 }
 memset(buffer,' ',MAX);
 read(sockfd,buffer,MAX);
 status=processRcptTo(buffer);
 if(status==250)
 {
  printf("250 OK\n");
  sprintf(msg,"%d OK",status);
  write(sockfd,msg,sizeof(msg));
 }
 else if(status==501)
 {
  sprintf(msg,"%d wrong domain",status);
  write(sockfd,msg,sizeof(msg));
  close(sockfd);
  exit(0);
 }
 else if(status==503)
 {
  sprintf(msg,"%d bad sequence",status);
  write(sockfd,msg,sizeof(msg));
  close(sockfd);
  exit(0);
 }
 memset(buffer,' ',MAX);
 read(sockfd,buffer,MAX);
 if(strncmp("DATA",buffer,4)==0)
 {
  printf("DATA command received...\n");
  sprintf(msg,"354 Start mail input; end with <CRLF>\n");
  write(sockfd,msg,sizeof(msg));
  handleData(sockfd);
 }
 else
 {
  sprintf(msg,"%d bad sequence",status);
  write(sockfd,msg,sizeof(msg));
  close(sockfd);
  exit(0);
 }
 memset(buffer,' ',MAX);
 read(sockfd,buffer,MAX);
 if(strncmp("QUIT",buffer,4)==0)
 {
  status=221;
  printf("QUIT command received...\n");
  sprintf(msg,"%d service closing",status);
  write(sockfd,msg,sizeof(msg));
 }
 else
 {
  sprintf(msg,"%d bad sequence",status);
  write(sockfd,msg,sizeof(msg));
  close(sockfd);
  exit(0);
 }
 close(sockfd);
}

void main()
{
 int sockfd,connfd,bindfd,len;
 struct sockaddr_in servaddr,cliaddr;
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
 servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
 servaddr.sin_port=htons(PORT);
 bindfd=bind(sockfd,(SA*)&servaddr,sizeof(servaddr));
 if(bindfd==0)
 printf("Socket binded successfully...\n");
 else
 {
  printf("Socket binding failed...\n");
  exit(0);
 }
 if(listen(sockfd,5)<0)
 {
  printf("Socket listen failed...\n");
  exit(0);
 }
 else
 printf("Socket listening on port %d\n",PORT);
 len=sizeof(cliaddr);
 connfd=accept(sockfd,(SA*)&cliaddr,&len);
 if(connfd<0)
 {
  printf("Connection failed...\n");
  exit(0);
 }
 else
 printf("Connection successful...\n");
 processMail(connfd);
 close(sockfd);
}