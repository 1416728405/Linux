#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void alarm_sig(int n){
	
}

unsigned int mysleep(unsigned int n){
	int val;
	struct sigaction act, oact;
	act.sa_flags = 0;
	act.sa_handler = alarm_sig;
	sigemptyset(&act.sa_mask);
	sigaction(SIGALRM, &act, &oact);

	sigset_t set,oset;
	sigemptyset(&set);
	sigaddset(&set, SIGALRM);
	sigprocmask(SIG_SETMASK, &set, &oset);

	val = alarm(n);
	sleep(3);
	sigsuspend(&act.sa_mask);
	//pause();
	return val;
}

int main(){
	while(1){
		printf("mysleep(2)\n");
		mysleep(2);
	}
}
