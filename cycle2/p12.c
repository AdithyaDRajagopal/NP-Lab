#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{
 int n,i,j,min,v,w,cost[10][10],dist[10],source,flag[10],last[10];
 char s[10];
 printf("Enter the number of routers : ");
 scanf("%d",&n);
 printf("Enter * for non-neighbouring vertices...\n");
 printf("Enter the cost matrix:\n");
 for(i=0;i<n;i++)
 printf("\tN%d",i);
 printf("\n");
 for(i=0;i<n;i++)
 {
  printf("N%d\t",i);
  for(j=0;j<n;j++)
  {
   scanf("%s",s);
   if(strcmp(s,"*")==0)
   cost[i][j]=9999;
   else
   cost[i][j]=atoi(s);
  }
 }
 printf("Enter the source router : N");
 scanf("%d",&source);
 for(i=0;i<n;i++)
 {
  cost[i][i]=0;
  dist[i]=cost[source][i];
  flag[i]=0;
  last[i]=source;
 }
 flag[source]=1;
 for(i=0;i<n;i++)
 {
  min=9999;
  for(w=0;w<n;w++)
  if(flag[w]==0)
  if(dist[w]<min)
  {
   min=dist[w];
   v=w;
  }
  flag[v]=1;
  for(w=0;w<n;w++)
  if(!flag[w])
  if(min+cost[v][w]<dist[w])
  {
   dist[w]=min+cost[v][w];
   last[w]=v;
  }
 }
 for(i=0;i<n;i++)
 {
  printf("\n");
  printf("N%d ==> N%d\n",source,i);
  w=i;
  printf("Path Taken : N%d ",i);
  while(w!=source)
  {
   w=last[w];
   printf("<-- N%d ",w);
  }
  printf("\nShortest path cost : %d\n",dist[i]);
 }
}
