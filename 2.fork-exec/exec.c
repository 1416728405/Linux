#include<stdio.h>
#include<stdlib.h>
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
		printf("parent..\n");
		while(1)
			sleep(1);
	}else if(pid == 0){
		if(i == 0){
			printf("child pid = %d, i = %d, exec ls -l\n", getpid(), i);
			execl("/bin/ls", "ls", "-l", NULL);
		}else if(i == 1){
			printf("child pid = %d, i = %d, exec touch A\n", getpid(), i);
			execl("/usr/bin/touch", "touch", "A", NULL);
		}else if(i == 2){
			printf("child pid = %d, i = %d, exec firefox A\n", getpid(), i);
			execl("/usr/bin/firefox", "firefox", "www.baidu.com", NULL);
		}

	}else{
		perror("fork failed");
	}
	return 0;
}
