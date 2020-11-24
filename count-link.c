#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
int describeASocket() {
 int socket_descriptor = 0;
 socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
 if (socket_descriptor < 0) {
   printf("\n\n   ==========   FAILED TO INITIATE A SOCKET ====================  \n\n");
   exit(0);
 }
 return socket_descriptor;
}

void connect_To_Server(int socket_descriptor) {
 struct sockaddr_in server;
 server.sin_family = AF_INET;
 server.sin_port = htons(80);
 server.sin_addr.s_addr = inet_addr("216.58.223.142");
 int connection = connect(socket_descriptor, (struct sockaddr * ) & server, sizeof(server));
 if (connection != 0) {
   printf("\n\n  ==============  FAILED TO CONNECT TO THE SERVER ========================\n\n");
   exit(0);
 }
}
void sendMessage(int socket_descriptor) {
 char * message = "GET / HTTP/1.1 \r\n\r\n";
 int is_sent = send(socket_descriptor, message, strlen(message), 0);
 if (is_sent < 0) {
   printf("\n\n  =======================  FAILED TO SEND THE MESSAGE  ======================\n\n");
   exit(0);
 }
}
void recieveMessage(int socket_descriptor) {
 FILE * googleFile;
 googleFile = fopen("google.html", "w");
 char responce[1000];
 int is_recv = -1;
 int count =0,i;
 while (is_recv = recv(socket_descriptor, responce, sizeof(responce), 0)) {
 for (i=1;i<1000;i++){
 if( responce[i] =='a' && responce[i-1]=='<'){
count = count+1;
}
 }
 fprintf(googleFile, "%s", responce);
}
printf("The file has %d links\n\n", count);
 fclose(googleFile);
 if (is_recv < 0) {
   printf("\n\n  =======================  FAILED TO RECIEVE THE MESSAGE  ======================\n\n");
   exit(0);
 }
}
/*int countLinks(){*/
/*  FILE * fp;*/
/*   char responce[1000];*/
/*  int count = 0,i=0; // Line counter (result) */
/*  // Open the file */
/* fp = fopen("google.html", "r");*/
/*  // Check if file exists */
/*  if (fp == NULL) {*/
/*    printf("Could not open file");*/
/*    exit(1);*/
/*  }*/
/*  char word[3] = "<a";*/
/*  char chars[2];*/
/*  // Extract characters from file and store in character c */
/*  int indicator = 0;*/
/*  char c;*/
/* for (i=1;i<1000;i++) {*/
/* c = getc(fp);*/
/*if( responce[i] =='a' && responce[i-1]=='<'){*/
/*count = count+1;*/
/*}*/
/*  }*/
/*  // Close the file */
/* */
/*  fclose(fp);*/
/*}*/
void main() {
 char * responce;
 int socket_descriptor = describeASocket(); // step one
 connect_To_Server(socket_descriptor); //step two
 sendMessage(socket_descriptor); //step three
 recieveMessage(socket_descriptor); //step four
 //countLinks();
}
