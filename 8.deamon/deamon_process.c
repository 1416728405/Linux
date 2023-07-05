#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<time.h>

void deamon_business(){
	time_t tm;
	char buf[1024];
	bzero(buf, 1024);
	int fd;
	if((fd = open("time.log", O_RDWR | O_CREAT, 0664)) == -1){
		perror("open failed");
		exit(0);
	}
	while(1){
		tm = time(NULL);
		ctime_r(&tm, buf);
		write(fd, buf, strlen(buf));
		bzero(buf, 1024);
		sleep(3);
	}
}

void deamon_create(){
	pid_t pid = fork();
	if(pid > 0){
		exit(0);
	}else if(pid == 0){
		setsid();
		int fd = open("ERROR", O_RDWR|O_CREAT, 0664);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);

		chdir("./");
		umask(0002);

		deamon_business();

	}else{
		perror("fork failed");
		exit(0);
	}
}

int main(){
	deamon_create();	
}




