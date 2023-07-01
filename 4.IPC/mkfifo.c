#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define MSG "hello"

int main(){
	int fd;
	mkfifo("mkfifo", 0664);
	fd = open("mkfifo", O_WRONLY);
	write(fd, MSG, strlen(MSG));
	printf("write success\n");
	close(fd);
}

