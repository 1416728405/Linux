#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(){
	printf("1\n");
	pid_t pid = fork();
	printf("2\n");
	if(pid > 0){
		printf("parent...\n");
		while(1)
			sleep(1);
	}else if(pid == 0){
		printf("child...\n");
		while(1);
	}else{
		perror("fork error..\n");
	}

}

