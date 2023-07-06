#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>

void sig_do(int n){
	printf("SIGNAL %d SIGINT\n", n);
}

int main(){
	struct sigaction act,oact;
	act.sa_flags = 0;
	act.sa_handler = sig_do;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, &oact);

	int len;
	char buf[1024];
	bzero(buf,1024);
	
tryAgain:
	while((len = read(STDIN_FILENO, buf, 1024)) > 0){
		printf("%s\n", buf);
		bzero(buf,1024);
	}
	if(len == -1){
		if(errno == EINTR){
			printf("read return value EINTER\n");
			goto tryAgain;
		}
	}
}
