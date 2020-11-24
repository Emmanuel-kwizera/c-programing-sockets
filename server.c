#include <sys/socket.h>
//#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>

int main(){

int descriptor = socket(AF_INET,SOCK_STREAM,0);

if(descriptor<0){
        printf("Failed to initiate the socket!\n");
exit(0);
}

//binding  the IP and port to the socket identified
    struct sockaddr_in server;
    server.sin_family=AF_INET;//AF_INET6
    server.sin_port= htons(8090);
    server.sin_addr.s_addr=inet_addr("172.0.0.1");
    
int  bind_status = bind(descriptor, (struct sockaddr *)&server  ,sizeof(server));

if(bind_status<0){
        printf("Failed to Bind the socket!\n");
exit(0);
}


//LISTE FOR INCOMING CONNECTIONS from clients

int listeming_status=listen(descriptor,3)
if(listeming_status<0){
        printf("Failed to listen to incoming connection request!\n");
exit(0);
}

int addrlen=sizeof(server);

int new_descriptor = accept(descriptor,(struct sockaddr *)&server,(socklen_t*)&addrlen);

// Receive requests from the client
char request_from_client[3000];
int size_of_client_request=0;

if(size_of_client_request<=0){
printf("No request was received!!!!!!!!!");
exit(0);
}

printf("request_from_client: %s\n",request_from_client);
char *response_to_the_clinet="Your request was received!!!!!!!!!";

if(response_to_the_clinet<0){
printf("");
exit(0);
}


size_of_client_request=recv(accept_new_socket_descriptor,request_from_client,strlen(request_from_client),0);  //read()
// OPTIONALY SET the socket
/*int optval=1;
int levelValue = SOL_SOCKET;
printf("levelValue: %d",levelValue);
int status = setsocketopt(descriptor,SOL_SOCKET,);
int  setsocketopt(int sockfd,int level, int optname,
		const void * optval, ocklen_t optlen);*/

return 0;
}
