#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

pid_t child_pid;

void parent_sig(int n, siginfo_t* info, void *arg){
	printf("parent pid %d, recv num = %d\n", getpid(), info->si_int);
	union sigval val;
	val.sival_int = (info->si_int) + 1;
	sigqueue(child_pid, SIGUSR1, val);
	sleep(1);
}

void child_sig(int n, siginfo_t* info, void *arg){
	printf("child pid %d, recv num = %d\n", getpid(), info->si_int);
	union sigval val;
	val.sival_int = (info->si_int) + 1;
	sigqueue(getppid(), SIGUSR2, val);
	sleep(1);
}

int main(){
	struct sigaction act, oact;
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = parent_sig;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR2, &act, &oact);

	sigset_t set, oset;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigprocmask(SIG_SETMASK, &set, &oset);
	
	pid_t pid;
	pid = fork();
	if(pid >0){
		child_pid = pid;
		union sigval val;
		val.sival_int = 0;
		sigqueue(pid, SIGUSR1, val);
		while(1)
			sleep(1);
	}else if(pid == 0){
		struct sigaction act, oact;
		act.sa_flags = SA_SIGINFO;
		act.sa_sigaction = child_sig;
		sigemptyset(&act.sa_mask);
		sigaction(SIGUSR1, &act, &oact);
		sigprocmask(SIG_SETMASK, &act.sa_mask, NULL);
		while(1)
			sleep(1);
	}else{
		perror("fork failed");
		exit(0);
	}

}
