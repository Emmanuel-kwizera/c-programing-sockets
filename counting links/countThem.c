#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//FUNCTION TO INITIALIZE THE SOCKET
int socketInitializer(){
	int descriptor = socket(AF_INET,SOCK_STREAM,0);

    	if(descriptor<0){
        	printf("FAILED TO INITIALISE THE SOCKET!!\n");
		//exit(0);
    	}
   	return descriptor;

}

//FUNCTION TO CREATE THE CONNECTION 
int connectMe(int descriptor){
	struct sockaddr_in server;
    	server.sin_family=AF_INET;//AF_INET6
    	server.sin_port= htons(80);
    	server.sin_addr.s_addr=inet_addr("216.58.223.110");
	int con = connect(descriptor,  (struct sockaddr *)&server  ,sizeof(server));

 	if(con!=0){
        	printf("CONNECTION FAILED!!\n");
        	//exit(0);
    	}
    	return con;

}


//FUNCTION TO SEND A MESSAGE
void sendMessage(int descriptor){
    	char * message ="GET / HTTP/1.1\r\n\r\n";
	int sent_status = send(descriptor,message,strlen(message),0);

   	if(sent_status < 0){
        	printf("MESSAGE NOT SENT!!\n");
		//exit(0);
    	}

}

//FUNCTION TO RETURN THE RESPONCE/NUMBER OF LINKS IN THE PAGE 
void recieve_responce(int descriptor){
	FILE * googleFile;
 	googleFile = fopen("google.html", "w");
 	char responce[50000];
 	int is_recv = -1;
 	int count =0;
 	while (is_recv = recv(descriptor, responce, sizeof(responce), 0)) {
 		for (int i=1;i<=50000;i++){
 			if( responce[i] =='a' && responce[i-1]=='<' && responce[i+1]==' '){
				count = count+1;
			}
 		}
 	fprintf(googleFile, "%s", responce);
	}

	printf("\nTHE FILE HAS %d LINKS\n\n", count);
 	fclose(googleFile);
 	if (is_recv < 0) {
  		 printf("\n\n RESPONCE NOT SENT!!\n\n");
  		 //exit(0);
 	}
}

//MAIN FUNCTION OF THE PROGRAM
int main(){

    	//1. INITIATING A SOCKET
    	//===========================================
    	int sock1 = socketInitializer();
    	//2. CREATING A CONNECTION TO THE SERVER
    	//===========================================
    	int descriptor = connectMe(sock1);
    	//3. SENDING REQUESTS
    	//===========================================
    	sendMessage(sock1);
   	//4. RECEIVING RESPONSES
    	//===========================================
    	recieve_responce(sock1);
    	// END CLOSE THE SOCKET CONNECTION
    	//===========================================
    	close(descriptor);

return 0;
}
