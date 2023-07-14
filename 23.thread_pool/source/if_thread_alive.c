#include<server.h>

int if_thread_alive(pthread_t tid){
	pthread_kill(tid, 0);
	if(errno == ESRCH)
		return 0;
	return 1;
}
