#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{
 int n,arr[10][10],dist[10][10],i,j,k;
 char s[10];
 printf("Enter the size of the distance matrix : ");
 scanf("%d",&n);
 printf("Enter * for non-neighbouring vertices...\n");
 printf("Enter the distance matrix:\n");
 for(i=0;i<n;i++)
 printf("\tN%d",i+1);
 printf("\n");
 for(i=0;i<n;i++)
 {
  printf("N%d\t",i+1);
  for(j=0;j<n;j++)
  {
   scanf("%s",s);
   if(strcmp(s,"*")==0)
   arr[i][j]=9999;
   else
   arr[i][j]=atoi(s);
   dist[i][j]=arr[i][j];
  }
 }
 for(i=0;i<n;i++)
 dist[i][i]=0;
 for(i=0;i<n;i++)
 for(j=0;j<n;j++)
 for(k=0;k<n;k++)
 if(dist[i][j]>arr[i][k]+dist[k][j])
 dist[i][j]=arr[i][k]+dist[k][j];
 printf("Reduced Distance Matrix:\n");
 for(k=0;k<n;k++)
 printf("\tN%d",k+1);
 printf("\n");
 for(i=0;i<n;i++)
 {
  printf("N%d",i+1);
  for(j=0;j<n;j++)
  printf("\t%d",dist[i][j]);
  printf("\n");
 }
}
