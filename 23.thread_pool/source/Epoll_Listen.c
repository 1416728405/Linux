#include<server.h>

int Epoll_Listen(int sockfd, pool_t *ptr){
	printf("Epoll_Listen..\n");
	int ready;
	int flag;
	bs_t tmp;
	struct epoll_event ready_array[EPOLLMAX];	

	while(ptr->thread_shutdown){
		flag = 0;
		if((ready = epoll_wait(epfd, ready_array, EPOLLMAX, -1)) == -1){
			perror("Epoll_Listen, epoll_wait error");
			exit(0);
		}

		while(ready){
		//	printf("ready = %d\n", ready);
			if(ready_array[flag].data.fd == sockfd){
				tmp.business = Business_Accept;
				tmp.arg = (void*)&sockfd;
				Producer_add_task(ptr, tmp);
			}else{
				tmp.business = Business_Retime;
				tmp.arg = (void*)&ready_array[flag].data.fd;
				Producer_add_task(ptr, tmp);
			}
			ready--;
			flag++;
		}

	}
	close(sockfd);
	return 0;
}
