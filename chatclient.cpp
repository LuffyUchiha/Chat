#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include<stdio.h>

using namespace std;

int main(int argc,char* argv[])
{
  if(argc != 4)
    {
      cerr << "Usage syntax: ./client <your_name> <ip_address> <port_no> " << endl;
      return 0;
    }
    string your_name=argv[1];
  int sockfd;
  struct sockaddr_in my_addr;

  sockfd=socket(PF_INET,SOCK_STREAM,0);

  my_addr.sin_family=AF_INET;
  my_addr.sin_port=htons(atoi(argv[3]));
  my_addr.sin_addr.s_addr=inet_addr(argv[2]);
  memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);

  int temp=connect(sockfd,(struct sockaddr*)&my_addr, sizeof my_addr);

  if(temp==0)
    cout << "Connection established with server" << endl;
  else
    {
      cout << "Could not establish connection!" << endl;
      return -1;
    }
  char * buffer;
  char buffer_recv[1000];
  buffer=new char[your_name.length()+1];
  strcpy(buffer,your_name.c_str());
  send(sockfd,buffer,sizeof buffer,0);
   recv(sockfd,buffer,sizeof buffer,0);
  string friend_name(buffer);
  string your_message;
  do{
  recv(sockfd,buffer_recv,sizeof buffer_recv,0);
  cout<<"\t\t\t\t"<<friend_name<<":"<<endl<<"\t\t\t\t"<<buffer_recv<<endl;
    cout<<your_name<<":"<<endl;
  getline(cin,your_message);
  buffer=new char[your_message.length()+1];
  strcpy(buffer,your_message.c_str());
  send(sockfd,buffer,your_message.length()+1,0);
  }while(your_message!="END");
   /* string your_message;
  do{
    cout<<your_name<<":"<<endl;
  getline(cin,your_message);
  buffer=new char[your_message.length()+1];
  strcpy(buffer,your_message.c_str());
  send(sockfd,buffer,your_message.length()+1,0);
  int rec=recv(sockfd,buffer,sizeof buffer,0);
  cout<<rec<<endl;
  if(rec>0)
  cout<<"\t\t\t\t"<<friend_name<<":"<<endl<<"\t\t\t\t"<<buffer<<endl;
  }while(your_message!="END");*/
  return 0;
  }
