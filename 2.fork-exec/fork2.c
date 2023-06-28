#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(){
	pid_t pid;
	int i;
	for(i = 0; i < 5; i++){
		pid = fork();
		if(pid == 0)
			break;
	}
	if(pid > 0){
		printf("parent...\n");
		while(1)
			sleep(1);
	}else if(pid == 0){
		if(i == 0){
			printf("child pid = %d, i = %d\n", getpid(), i);
		}else if(i == 1){
			printf("child pid = %d, i = %d\n", getpid(), i);
		
		}else{

		printf("child pid = %d...\n", getpid());
		//while(1);
		}
		while(1)
			sleep(1);
	}else{
		perror("fork error..\n");
	}

}

