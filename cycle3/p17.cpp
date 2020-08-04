#include<cstdio>
#include<iostream>
#include<pcap.h>
#include<sys/socket.h>
#include<pcap/pcap.h>
#include<netinet/in.h>
#include<netinet/if_ether.h>
#include<arpa/inet.h>
using namespace std;
int ipc=0;
int arpc=0;

void printit(u_int8_t *etherheader,int n)
{
 printf("%02x:%02x:%02x:%02x:%02x:%02x\n",etherheader[0],etherheader[1],
 	etherheader[2],etherheader[3],etherheader[4],etherheader[5]);
}

void callBack(u_char *args,const struct pcap_pkthdr *header,const u_char *packet)
{
 u_int8_t *src,*dest;
 struct ether_header *hdr=(struct ether_header *)packet;
 src=hdr->ether_shost;
 dest=hdr->ether_dhost;
 if(ntohs(hdr->ether_type)==ETHERTYPE_IP)
 {
  cout<<"Ethernet type hex "<<std::hex<<ntohs(hdr->ether_type)
      <<" decimal "<<std::dec<<ntohs(hdr->ether_type)<<" is an IP packet \n";
  cout<<"Received "<<++ipc<<" IP packets\n";
 }
 else if(ntohs(hdr->ether_type)==ETHERTYPE_ARP)
 {
  cout<<"Ethernet type hex "<<std::hex<<ntohs(hdr->ether_type)
      <<" decimal "<<std::dec<<ntohs(hdr->ether_type)<<" is an ARP packet\n";
  cout<<" Received "<<++ipc<<" ARP packets\n";
 }
 cout<<"Destination address : ";
 printit(dest,ETHER_ADDR_LEN);
 cout<<"Source address : ";
 printit(src,ETHER_ADDR_LEN);
 cout<<endl;
}

int main()
{
 char errbuf[PCAP_ERRBUF_SIZE];
 pcap_t *handle;
 pcap_if_t *devs,*dev;
 int i,ch;
 struct bpf_program fp;
 if(pcap_findalldevs(&devs,errbuf)==-1)
 {
  cout<<errbuf<<"\n";
  exit(0);
 }
 cout<<"Select the interface of your choice:\n";
 for(dev=devs,i=0;dev;dev=dev->next)
 printf("%d. %s\n",i++,dev->name);
 cout<<"Enter your choice:";
 scanf("%d",&ch);
 for(dev=devs,i=-1;dev;dev=dev->next)
 if((++i)==ch)
 break;
 handle=pcap_open_live(dev->name,BUFSIZ,0,0,errbuf);
 if(handle==NULL)
 {
  cout<<"Could not open device "<<dev->name<<":"<<errbuf<<"\n";
  exit(0);
 }
 pcap_loop(handle,10,callBack,NULL);
 return 0;
}
