#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	pid_t pid;
	int i;
	for(i = 0; i < 2; i++){
		pid = fork();
		if(pid == 0)
			break;
	}

	if(pid > 0){
		pid_t zpid;
		int status;
		while((zpid = wait(&status)) > 0){
			if(WIFEXITED(status)){
				printf("parent wait child pid = %d success normal exit, exit code = %d\n", zpid, WEXITSTATUS(status));
			}
			if(WIFSIGNALED(status)){
				printf("parent wait child pid = %d success abnormal exit, signal code = %d\n", zpid, WTERMSIG(status));

			}
		}
	}else if(pid == 0){
		if(i == 0){
			printf("child i = %d, pid = %d\n", i, getpid());
			sleep(5);
			exit(5);
		}else if(i == 1){
			while(1){
				printf("child i = %d, pid = %d sleep\n", i, getpid());
				sleep(1);
			}
		}
	}else{
		perror("fork failed");
	}
}
