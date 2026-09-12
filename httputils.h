#ifndef HTTPUTILS_H
#define HTTPUTILS_H

int isValidMethod(char* method);
void getReturnType(char* filename, char* buffer);
void generateResponse(char *content, size_t length, char *returnType, char *buffer);
void generateHeaders(size_t length, char *returnType, char *buffer);

#endif
