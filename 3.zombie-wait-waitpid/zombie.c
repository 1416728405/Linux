#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	pid_t pid;
	int i;
	pid = fork();

	if(pid > 0){
		pid_t zpid;
		zpid = wait(NULL);
		printf("parent wait zpid = %d success\n", zpid);
		while(1)
			sleep(1);
	}else if(pid == 0){
		printf("child pid = %d\n", getpid());
		sleep(5);
		exit(0);		
	}else{
		perror("fork failed");
	}

}
