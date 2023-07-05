#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int main(){
	sigset_t new_set, old_set;

	sigemptyset(&new_set);
	
	sigaddset(&new_set, SIGINT);
	sigaddset(&new_set, SIGQUIT);
	sigaddset(&new_set, SIGKILL);

	sigprocmask(SIG_SETMASK, &new_set, &old_set);
	while(1)
		sleep(1);
}
