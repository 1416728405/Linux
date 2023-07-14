#include<server.h>

int Epoll_create(int sockfd){
	int epfd;
	if((epfd = epoll_create(EPOLLMAX)) == -1){
		perror("Epoll_create, epoll_create error");
		exit(0);
	}

	struct epoll_event node;
	node.data.fd = sockfd;
	node.events = EPOLLIN|EPOLLET;

	if(epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &node) == -1){
		perror("Epoll_create, epoll_ctl error");
		exit(0);
	}

	return epfd;
}
