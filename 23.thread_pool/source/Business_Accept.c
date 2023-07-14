#include<server.h>

void *Business_Accept(void *arg){
	printf("Business_Accept\n");
	int serverfd;
	int clientfd;
	socklen_t addrlen;
	struct sockaddr_in addr;
	struct epoll_event node;
	char clientip[16];
	char response[1500];

	bzero(response, 1500);
	bzero(clientip, 16);

	serverfd = *(int *)arg;
	addrlen = sizeof(addr);

	if((clientfd = accept(serverfd, (struct sockaddr*)&addr, &addrlen)) == -1){
		perror("Business_Accept, accept error");
		exit(0);
	}

	node.data.fd = clientfd;
	node.events = EPOLLIN | EPOLLET;
	if(epoll_ctl(epfd, EPOLL_CTL_ADD, clientfd, &node) == -1){
		perror("Business_Accept, epoll_ctl error");
		exit(0);
	}

	inet_ntop(AF_INET, &addr.sin_addr.s_addr, clientip, 16);
	sprintf(response ,"hi, <%s> Welcome", clientip);

	send(clientfd, response, strlen(response), MSG_NOSIGNAL);
	return NULL;
}
