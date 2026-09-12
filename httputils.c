#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isValidMethod(char *method){
	if(!strcmp(method, "GET") || !strcmp(method, "POST") || !strcmp(method, "PUT") || !strcmp(method, "DELETE") || !strcmp(method, "HEAD") || !strcmp(method, "OPTIONS"))
	{
		return 1;
	}
	return 0;
	}
void getReturnType(char* filename, char* buffer){
	char *extension = strrchr(filename, '.');
	if(extension == NULL){
		strcpy(buffer, "index");
		return;
	}
	extension++;
	if(!strcmp(extension, "html")){
		strcpy(buffer, "text/html");
	}
	else if(!strcmp(extension, "css")){
		strcpy(buffer, "text/css");
	}
	else if(!strcmp(extension, "js")){
		strcpy(buffer, "text/js");
	}
	else if(!strcmp(extension, "ico")){
		strcpy(buffer, "image/png");
	}
	else if(!strcmp(extension, "png")){
		strcpy(buffer, "image/png");
	}
	else{
		strcpy(buffer, "invalid");
	}
}
			
			
void generateResponse(char *responseBody,size_t length, char *returnType, char *buffer){
        char response[4096];
        int len = snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\n"
    "Content-Type: %s\r\n"
    "Content-Length: %zu\r\n"
    "Connection: close\r\n"
    "\r\n"
    "%s",returnType, length, responseBody);
        strcpy(buffer, response);
}

void generateHeaders(size_t length, char *returnType, char *buffer){
        char response[4096];
        int len = snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\n"
    "Content-Type: %s\r\n"
    "Content-Length: %zu\r\n"
    "Connection: close\r\n"
    "\r\n"
    ,returnType, length);
        strcpy(buffer, response);
}

