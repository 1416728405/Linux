#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void printf_sigmember(sigset_t* set){
	for(int i = 1; i < 32; i++){
		if(sigismember(set, i)){
			printf("1");
		}else{
			printf("0");
		}
		fflush(stdout);
	}
	printf("\n");
}

int main(){
	sigset_t new_set, old_set, pset;
	sigemptyset(&new_set);
	sigaddset(&new_set, SIGINT);
	sigprocmask(SIG_SETMASK, &new_set, &old_set);
	while(1){
		sigpending(&pset);
		printf_sigmember(&pset);
		sleep(1);
	}
}
