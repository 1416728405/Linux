#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){
	int fd;
	char buf[1024];
	bzero(buf, 1024);
	
	fd = open("mkfifo", O_RDONLY);
	read(fd, buf, 1024);
	printf("read buf : %s\n", buf);
	
	close(fd);
	return 0;
}


