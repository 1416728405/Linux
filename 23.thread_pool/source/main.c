#include<server.h>

int main(){
	int sockfd;
	pool_t *ptr = NULL;
	sigset_t set,oset;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigprocmask(SIG_SETMASK, &set, &oset);

	sockfd = Net_init();
	epfd = Epoll_create(sockfd);
	ptr = thread_pool_create(300, 10, 1000);
	PTR = ptr;
	Epoll_Listen(sockfd, ptr);

	if(!ptr->thread_shutdown){
		thread_pool_destroy(ptr);
	}
	return 0;
}
