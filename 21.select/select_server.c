#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<time.h>



#define SERVER_IP "192.168.206.132"
int client_array[1020];

int socket_init(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		perror("socket error");
		exit(0);
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);

	if(bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1){
		perror("bind error");
		exit(0);
	}

	if(listen(sockfd, 128) == 1){
		perror("listen error");
		exit(0);
	}

	return sockfd;
}

int return_response(int clientfd, const char *client_ip){
	char response[1024];
	bzero(response, 1024);
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = inet_addr(client_ip);
	
	sprintf(response, "hi <%s> welcome..\n", client_ip);
	printf("%s", response);
	send(clientfd, response, strlen(response), 0);
	return 0;
}


int main(){
	int serverfd, clientfd, maxfd;
	int SHUTDOWN = 1;
	int ready;
	struct sockaddr_in clientaddr;
	int addrlen;
	time_t tp;
	socklen_t recvlen;
	fd_set set,oset;
	char client_ip[16];
	char recv_buf[1500];
	char time_buf[1024];
	bzero(recv_buf, 1500);
	bzero(time_buf, 1024);
	bzero(client_ip, 16);

	for(int i = 0; i < 1020; i++){
		client_array[i] = -1;
	}
	
	serverfd = socket_init();
	maxfd = serverfd;
	FD_SET(serverfd, &set);

	printf("select server running..\n");
	while(SHUTDOWN){
		oset = set;
		ready = select(maxfd+1, &oset, NULL, NULL, NULL);

		while(ready){
			addrlen = sizeof(clientaddr);
			if(FD_ISSET(serverfd, &oset)){
				if((clientfd = accept(serverfd, (struct sockaddr*)&clientaddr, &addrlen)) == -1){
					perror("accept error");
					exit(0);
				}
				inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, client_ip, 16);
				return_response(clientfd, client_ip);
				if(maxfd < clientfd){
					maxfd = clientfd;
				}
				FD_SET(clientfd, &set);
				for(int i = 0; i < 1020; i++){
					if(client_array[i] == -1){
						client_array[i] = clientfd;
						break;
					}
				}
				FD_CLR(serverfd, &oset);
			}else{
				int i;
				for(i = 0 ; i < 1024; i++){
					if(FD_ISSET(client_array[i], &oset)){
						clientfd = client_array[i];
						break;
					}
				}
				recvlen = recv(clientfd, recv_buf, sizeof(recv_buf), 0);
				if(recvlen > 0){
					if(strcmp(recv_buf, "localtime\n") == 0){
						tp = time(NULL);
						ctime_r(&tp, time_buf);
						send(clientfd, time_buf, strlen(time_buf), 0);
						bzero(time_buf, 1024);
					}else{
						send(clientfd, "Please Try Again\n", 17, 0);
					}
				}else{
					printf("user close, clientfd = %d\n", clientfd);
					close(clientfd);
					FD_CLR(clientfd, &set);
					client_array[i] = -1;
				}
				FD_CLR(clientfd, &oset);	
			}

			--ready;
		}
	}

}
