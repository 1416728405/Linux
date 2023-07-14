#include<server.h>

void *print_thread(void *arg){
	pthread_detach(pthread_self());
	pool_t *ptr = (pool_t*)arg;

	struct sigaction act, oact;
	act.sa_flags = 0;
	act.sa_handler = sig_usr;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, &oact);
	sigprocmask(SIG_SETMASK, &act.sa_mask, NULL);

	while(ptr->thread_shutdown){
		sleep(TIMEOUT);
	}

	return NULL;
}
