#include<stdio.h>
#include<time.h>
void main()
{
 time_t t;
 time(&t);
 char *str=ctime(&t);
 int len=sizeof(str);
 printf("%s",str);
 printf("%d",len);
}
