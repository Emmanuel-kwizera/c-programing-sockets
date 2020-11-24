#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

//defining the socket
int socket_descriptor=socket(AF_INET,SOCK_STREAM,0);
if(socket_descriptor<0){
printf("Failed to initiate the socket!\n");
}

//optionally set the socket
int optional=0;
int socket_status= setsockopt(socket_descriptor,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT ,&optional,sizeof(optional));
//int setsocktop(int sockfd,int level, int optname,const void *option_value, socklen_t option_length);
if(socket_status<0){
   printf("The socket was not initiated!\n");
   exit(0);
}

//bind the ip and port to the socket
struct sockaddr_in server;
// server.sin_addr.s_addr=inet_addr("172.0.0.1");
server.sin_family=AF_INET;
server.sin_port=htons(8090);
server.sin_addr.s_addr=htonl(INADDR_ANY);//converts the unsigned integer hostlong from host byte order to network byte order
//inaddr-any take the localhost of this computer
int addrlen= sizeof(server);
int binding_satus=bind(socket_descriptor,(struct sockaddr *)&server,addrlen);
if(binding_satus<0){
printf("Can't bind to socket !\n");
exit(0);
}
//int bind(int sockfd, const struct sockaddr *addr,   socklen_t addrlen);
printf("Bind successful\n");

// 4. LISTEN ON sockect identified by the port and ip
int listening_status=listen(socket_descriptor,4);
if(listening_status<0){
   printf("Couldn't listen for incoming requests\n");
   exit(0);
}

// 5. Start the client related tasks
printf("Waiting for requests !!!!!\n");
int accept_new_socket_descriptor=accept(socket_descriptor, (struct sockaddr*)&server, (socklen_t*)&addrlen);
printf("Waiting for requests !!!!!\n");
if(accept_new_socket_descriptor<=0){
printf("Connection reject!");
exit(0);
}

//6. Receive requests from the client
char request_from_client[1000];
int size_of_client_request=0;
//size_of_client_request= read( new_socket , buffer, 1024);
size_of_client_request=recv(accept_new_socket_descriptor,request_from_client,sizeof(request_from_client),0);  //read()
printf("request_from_client: %s\n",request_from_client);
char *response_to_the_clinet="Your request was received!!!!!!!!!\n Now its on the server!!!!!!";
int response_sent_status=send(accept_new_socket_descriptor,response_to_the_clinet,strlen(response_to_the_clinet),0);// write
//  end of conversation
printf("Our Dialogue is Ended!!!!!!!!!!!!!!\n");
printf("Thank you very much!!!!!!!!!!!!!!\n");
return 0;
}

