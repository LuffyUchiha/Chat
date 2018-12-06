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
template<size_t N>
string convert(char const(&data)[N])
{
   return string(data, find(data, data + N, '\0'));
}
int main(int argc,char* argv[])
{
  if(argc !=3)
    {
      cerr << "Usage syntax: ./server <your_name> <port_no>" << endl;
      return 0;
    }
    string your_name=argv[1];
  int sockfd,sockfd1;
  struct sockaddr_in my_addr;
  fd_set master,read_fds;
  FD_ZERO(&master);
  FD_ZERO(&read_fds);
  sockfd=socket(PF_INET,SOCK_STREAM,0);  //Creating the socket
  my_addr.sin_family=AF_INET;
  my_addr.sin_port=htons(atoi(argv[2]));
  my_addr.sin_addr.s_addr=INADDR_ANY;
  memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);

  int temp=bind(sockfd, (struct sockaddr *)&my_addr, (sizeof my_addr)); //Binding the socket to the address
  if(temp==0)
    cout << "Server started running at "<< inet_ntoa(my_addr.sin_addr)  << ":" << argv[2] << endl;
  else
    {
      cout << "Failed to bind socket" << endl;
      return -1;
    }

  listen(sockfd,10);
  while(1)
  {
  struct sockaddr_in client_addr;
  socklen_t client_size=sizeof client_addr;
  int client_fd=accept(sockfd,(struct sockaddr*)&client_addr, &client_size);
  cout << "Accepted incoming connection" << endl;
  
  char * buffer=new char[your_name.length()+1];
  strcpy(buffer,your_name.c_str());
  send(client_fd,buffer,sizeof buffer,0);
  char buffer_recv[1000];
  recv(client_fd,buffer_recv,sizeof buffer_recv,0);
  string friend_name(buffer_recv);
  string your_message;
  do{
  cout<<your_name<<":"<<endl;
  getline(cin,your_message);
  buffer=new char[your_message.length()+1];
  strcpy(buffer,your_message.c_str());
  send(client_fd,buffer,your_message.length()+1,0);
  recv(client_fd,buffer_recv,sizeof buffer_recv,0);
  cout<<"\t\t\t\t"<<friend_name<<":"<<endl<<"\t\t\t\t"<<buffer_recv<<endl;  
  }while(your_message!="END");
  /*
  do{
  cout<<your_name<<":"<<endl;
  getline(cin,your_message);
  buffer=new char[your_message.length()+1];
  strcpy(buffer,your_message.c_str());
  send(client_fd,buffer,your_message.length()+1,0);
  int rec=recv(client_fd,buffer_recv,sizeof buffer_recv,0);
  cout<<rec<<endl;
  if(rec>0)
  cout<<"\t\t\t\t"<<friend_name<<":"<<endl<<"\t\t\t\t"<<buffer_recv<<endl;
  }while(your_message!="END");*/
  }
  return 0;
}
