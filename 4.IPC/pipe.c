#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

#define MSG "hello"


int main(){
	pid_t pid;
	int fds[2];

	pipe(fds);

	pid = fork();

	if(pid > 0){
		close(fds[0]);
		write(fds[1], MSG, strlen(MSG));
		close(fds[1]);
		wait(NULL);
	}else if(pid == 0){
		close(fds[1]);
		char buf[1024];
		bzero(buf, 1024);
		read(fds[0], buf, 1024);
		printf("chilid read msg:%s\n", buf);
		close(fds[0]);
		exit(0);
	}else{
		perror("fork failed");
	}
}

