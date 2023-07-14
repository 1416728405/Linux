#include<server.h>

void *Business_Retime(void *arg){
	int clientfd;
	int recvlen;
	time_t tp;
	char time_buf[1024];
	char recv_buf[1024];
	bzero(time_buf, 1024);
	bzero(recv_buf, 1024);

	clientfd = *(int*)arg;

	while((recvlen = recv(clientfd, recv_buf, sizeof(recv_buf), MSG_DONTWAIT)) == -1){
		if(errno == EINTR){
			break;
		}else{
			perror("Business_Retime, recv error");
			exit(0);
		}
	}

	if(recvlen == 0){
		close(clientfd);
		epoll_ctl(epfd, EPOLL_CTL_DEL, clientfd, NULL);
	}else if(recvlen > 0){
		if(strcmp(recv_buf, "time\n") == 0){
			tp = time(NULL);
			ctime_r(&tp, time_buf);
			send(clientfd, time_buf, strlen(time_buf), MSG_NOSIGNAL);
		}else{
			send(clientfd, "Please try again\n", 17, MSG_NOSIGNAL);
		}
	}

	return NULL;
}
