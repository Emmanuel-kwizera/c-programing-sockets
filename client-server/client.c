#include<sys/socket.h>
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <arpa/inet.h> 
#include <string.h>

int main(){

//Declare socket variables

int descriptor=-1;

//initiate a socket
descriptor=socket(AF_INET,SOCK_STREAM,0);
if(descriptor<0){
return 0;
}

struct sockaddr_in server;

server.sin_addr.s_addr=inet_addr("127.0.0.1");//convert host to network byte
server.sin_family=AF_INET;
server.sin_port=htons(8090);
//connect to the server
int connection= connect(descriptor,(struct sockaddr*)&server, sizeof(server));
if(connection!=0){
return 0;
}
char * request_data="Hello world";

//send request to the server
int is_sent=send(descriptor,request_data,strlen(request_data),0);
if(is_sent<0){
printf("Request not sent\n");
return 0;
}

//receive response
char response_buffer[500000];
int is_received=recv(descriptor,response_buffer,sizeof(response_buffer),0);
if(is_received<0){
printf("No response Sent\n");
return 0;
}

printf("The response is : %s\n",response_buffer);
return 0;
}



