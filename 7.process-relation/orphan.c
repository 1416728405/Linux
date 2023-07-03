#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(){
	pid_t pid;
	pid = fork();

	if(pid > 0){
		printf("parent pid = %d, ppid = %d\n", getpid(), getppid());
		exit(0);
	}else if(pid == 0){
		while(1)
		{
			sleep(1);
			printf("parent pid = %d, ppid = %d\n", getpid(), getppid());
		}
	}else{
		perror("fork failed");
		exit(0);
	}
}
