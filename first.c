#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <string.h> 



 
int main(){
struct sockaddr_in server;
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if( sockfd < 0){
		printf("Addres not Found");
		exit;
	}

//server	
server.sin_addr.s_addr = inet_addr("216.58.223.78");
server.sin_family = AF_INET;
server.sin_port = htons(80);
//connecting....

int conn = connect(sockfd, (struct sockaddr *)&server,sizeof(server));

if(conn != 0){
exit;
}

//printing....
int valread = read(sockfd , buffer, 1024); 
    printf("%s\n",buffer ); 
    send(sockfd, hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 

return 0;
}
