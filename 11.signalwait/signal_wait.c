#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void sigWait(int n){
	pid_t pid;
	while((pid = waitpid(-1, NULL, WNOHANG)) != -1){
		if(pid > 0){
			printf("parent pid = %d, wait success child pid = %d\n", getpid(), pid);
		}
	}
}

int main(){
	struct sigaction act,oact;
	act.sa_flags = 0;
	act.sa_handler = sigWait;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD, &act, &oact);

	pid_t pid;
	int i;
	for(i = 0; i < 5; i++){
		pid = fork();
		if(pid == 0)
			break;
	}

	if(pid > 0){
		printf("parent pid = %d, wait..\n", getpid());
		while(1)
			sleep(1);
	}else if(pid == 0){
		printf("child pid = %d, sleep %ds\n", getpid(), i);
		sleep(i);
		exit(0);
	}else{
		perror("fork failed");
		exit(0);
	}
}
