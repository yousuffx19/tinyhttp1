#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int isDir(char *filePath){
	int fd = open(filePath, O_RDONLY);
	struct stat ftype;
        fstat(fd, &ftype);
        if((ftype.st_mode & S_IFMT) == S_IFDIR){
               return 1;
        }
	return 0;
}	

void generateDirectoryHTML(char *dirPath, char *destBuffer, char *displayPath){
	int testfile = open(dirPath, O_RDONLY);
	DIR* mydir = fdopendir(testfile);
	struct dirent* test = readdir(mydir);
        if(test == NULL){
                printf("Directory not found\n");
                exit(0);
        }
	char HTML[4096] = "<!DOCTYPE html><h2>Index of \0";
	strcat(HTML, displayPath);
	strcat(HTML, "</h2><br>");
        while(test != NULL){
                if(!strcmp(test->d_name, ".") || !strcmp(test->d_name, "..")){
                	printf("ignoring...\n");
                }
                else{
			strcat(HTML, "<a href=\"\0");
			strcat(HTML, test->d_name);
			if(test->d_type == 4){
			strcat(HTML, "/");
			}
			strcat(HTML, "\">");
			strcat(HTML, test->d_name);
			strcat(HTML, "</a><br>");
                }
                test = readdir(mydir);
        }
	strcpy(destBuffer, HTML);
}
