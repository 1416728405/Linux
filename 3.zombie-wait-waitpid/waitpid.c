#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	pid_t pid;
	pid = fork();

	if(pid > 0){
		pid_t zpid;
		while((zpid = waitpid(-1, NULL, WNOHANG)) != -1){
			if(zpid > 0){
				printf("parent wait child success,  zpid = %d\n", zpid);
			}else if(zpid == 0){
				printf("parent running\n");
				sleep(1);
			}
		}
	}else if(pid == 0){
		printf("child pid = %d\n", getpid());
		sleep(5);
	}else{
		perror("fork failed");
	}
}


