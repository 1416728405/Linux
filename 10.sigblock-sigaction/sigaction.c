#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void sig_do(int n){
	printf("SIGINT 2\n");
}

int main(){
	struct sigaction act,oact;
	act.sa_handler = sig_do;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, &oact);

	while(1)
		sleep(1);
}
