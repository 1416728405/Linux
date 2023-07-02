#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


int main(){
	pid_t pid;
	int i;
	for(i = 0; i < 3; i++){
		pid = fork();
		if(pid == 0)
			break;
	}

	if(pid > 0){
		printf("parent pid = %d, ppid = %d, pgid = %d\n", getpid(), getppid(), getpgrp());
		while(1)
			sleep(1);

	}else if(pid == 0){
		printf("child pid = %d, ppid = %d, pgid = %d\n", getpid(), getppid(), getpgrp());
		if(i == 2){
			setpgid(getpid(), getpid());
		printf("i= 2 chiled pid = %d, ppid = %d, pgid = %d\n", getpid(), getppid(), getpgrp());
		}
		exit(0);
	}else{
		perror("fork failed");
		exit(0);
	}

}

