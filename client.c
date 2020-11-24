#include<sys/socket.h>
#include<arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include<unistd.h>



// here we are going to put all the things in the functions in order to make good look in our life

//socket initiator
int socketInitiator(){
    int socket_descriptor=socket(AF_INET,SOCK_STREAM,0);
    
    if(socket_descriptor<0){
        printf("Failed to initiate the socket!\n");
    }
    return socket_descriptor;
}
//serveer connector
int connect_to_server(int socket_descriptor){
    struct sockaddr_in server;
    server.sin_family=AF_INET;//AF_INET6
    server.sin_port= htons(80);
    server.sin_addr.s_addr=inet_addr("216.58.223.142");
    
    int connection=connect(socket_descriptor,  (struct sockaddr *)&server  ,sizeof(server));
    
    if(connection!=0){
        printf("Connection Failed!\n");
        return 0;
    }
    return connection;
}
// request_sender
void send_message(int socket_descriptor){
    char *msg="GET / HTTP/1.1\r\n\r\n";
    int is_sent = send(socket_descriptor,msg,strlen(msg),0); //or write(....)
    
    if(is_sent<0){
        printf("Message not sent!\n");
    }
}
//responce_reciever

void recieve_responce(int socket_descriptor){
    char response[2000];
    FILE *myGoogleFile;
    int is_received=recv(socket_descriptor,response,sizeof(response),0); // or the read(...)
    
    if(is_received < 0){
        printf("Message not recieved!\n");
    }
    
    printf("The response is :%s\n",response);
}

int main(){
    //1. INITIATING A SOCKET
    //======================
    int num1 = socketInitiator();
    //2. CREATING A CONNECTION TO THE SERVER
    //====================================
    int socket_descriptor = connect_to_server(num1);
    //3. SENDING REQUESTS
    //===========================================
    send_message(num1);
    //4. RECEIVING RESPONSES
    //===========================================
    recieve_responce(num1);
    // end close the socket
    close(socket_descriptor);
    return 0;
}
