#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include "httputils.h"


ssize_t sendResponse(int socketd, void* response, int responseSize){
	ssize_t total = 0;
	while(total < responseSize){
		int bytesRead = send(socketd, response+total, responseSize-total, 0);
		if(bytesRead < 0){
			return -1;
		}
		total += bytesRead;
	}
	return total;
}

long getFileSize(char* filename){
	FILE* fptr = fopen(filename, "r");
	 if(fptr == NULL){                                                                                                               printf("Error in reading file\n");                                                                                      return 0;                                                                                                       }
	fseek(fptr, 0, SEEK_END);
        long fileSize = ftell((FILE*) fptr);
        printf("FILE SIZE: %ld\n", fileSize);
        fseek(fptr, 0, SEEK_SET);
	fclose(fptr);
	return fileSize;
}

size_t sendFile(int socketd, char* filename, size_t fileSize){
	char buffer[4096];
	FILE* fptr = fopen(filename, "r");                                                                                      if(fptr == NULL){                                                                                                               printf("Error in reading file\n");                                                                                      return 0;                                                                                                       }
	size_t readBytes = 0;
	while(readBytes < fileSize){
		int readNow = fread(buffer, 1, sizeof(buffer), fptr);
		sendResponse(socketd, buffer, readNow);
		readBytes += readNow;
	}
	return readBytes;

}


void mapRequest(int socketd, char *method, char *path, char *version){
	char response[4096];
	char returnType[16];
	if(!isValidMethod(method)){
		generateResponse("405 Method Not Allowed", strlen("405 Method Not Allowed"), "text/plain", response);
		send(socketd, response, sizeof(response), 0);
	}
	if(!strcmp(path, "/hello")){
		generateResponse("Hi", strlen("Hi"), "text/plain", response);
		send(socketd, response, sizeof(response),0);
	}
	else if(!strcmp(path, "/about")){
		generateHeaders(strlen("This is a very small HTTP server..."), "text/plain", response);
		send(socketd, response, strlen(response), 0);
                send(socketd, "This is a very small HTTP server...", sizeof("This is a very small HTTP server..."), 0);
	}
	else{
		getReturnType(path, returnType);
		if(!strcmp(returnType, "invalid")){
			 generateResponse("File type not supported...", strlen("File type not supported..."), "text/plain", response);
                	 send(socketd, response, sizeof(response), 0);
			 return;
		}
	       	if(!strcmp(returnType, "index")){
			strcat(path, "index.html");
		}	
		long fs = getFileSize(path+1);
		if(fs <= 0){
			generateResponse("404 Not Found", strlen("404 Not Found"), "text/plain", response);
                        sendResponse(socketd, response, sizeof(response));
			return;	
		}
		generateHeaders(fs, returnType, response);
	       	send(socketd, response, strlen(response), 0);	
		if(sendFile(socketd,path+1, fs) <= 0){
			       printf("Error in Sending File");
			       return;
		}
	}
}

void handleRequest(char *content, int socketd){
	char method[8];
	char path[512];
	char version[16];
	if(sscanf(content, "%15s %1023s %15s", method, path, version) != 3){
		printf("Error in parsing request line\n");
		exit(1);
	}
	printf("Method: %s\n", method);
	printf("Path: %s\n", path);
	printf("Version: %s\n", version);
	mapRequest(socketd, method, path, version);
}


void *handleConnection(void* arg){
	int conn = *((int *) arg);
 	printf("\nNew connection....\n");
        char recieveBuffer[2048];
        ssize_t bytesrecv = recv(conn, recieveBuffer, sizeof(recieveBuffer), 0);
        handleRequest(recieveBuffer, conn);
        close(conn);
	return arg;
}

int main(){
	printf("Server Started\n");
	int socketd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketd < 0){
		printf("Error Occured\n");
		exit(1);
	}
	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(8080);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	int listend = bind(socketd, (struct sockaddr *) &address, sizeof(address));
	if(listend < 0){
		printf("Error in binding socket\n");
		exit(1);
	}
	int lsn = listen(socketd, 1);
	struct sockaddr clientaddr;
	socklen_t clientaddrlen;
	while(1){
	int conn = accept(socketd, &clientaddr, &clientaddrlen);
        if(conn < 0){
                printf("Error occured in accepting connection");
        }
	pthread_t clientThread;
	pthread_create(&clientThread, NULL, &handleConnection, &conn);
        pthread_detach(clientThread);
	}
	return 0;
}
