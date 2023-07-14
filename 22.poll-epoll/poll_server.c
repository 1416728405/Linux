#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<time.h>
#include<sys/poll.h>


#define SERVER_IP "192.168.206.132"
struct pollfd client_array[10000];

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
	int serverfd, clientfd;
	int SHUTDOWN = 1;
	int ready;
	struct sockaddr_in clientaddr;
	int addrlen;
	time_t tp;
	socklen_t recvlen;
	
	char client_ip[16];
	char recv_buf[1500];
	char time_buf[1024];
	bzero(recv_buf, 1500);
	bzero(time_buf, 1024);
	bzero(client_ip, 16);

	for(int i = 0; i < 10000; i++){
		client_array[i].fd = -1;
		client_array[i].events = POLLIN;
	}
	
	serverfd = socket_init();
	client_array[0].fd = serverfd;

	printf("select server running..\n");
	while(SHUTDOWN){
		
		ready = poll(client_array, 10000, -1);

		while(ready){
			addrlen = sizeof(clientaddr);
			if(client_array[0].revents == POLLIN){
				if((clientfd = accept(serverfd, (struct sockaddr*)&clientaddr, &addrlen)) == -1){
					perror("accept error");
					exit(0);
				}
				inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, client_ip, 16);
				return_response(clientfd, client_ip);
				
				for(int i = 0; i < 10000; i++){
					if(client_array[i].fd == -1){
						client_array[i].fd = clientfd;
						break;
					}
				}
				client_array[0].revents = 0;
				
			}else{
				int i;
				for(i = 0 ; i < 10000; i++){
					if(client_array[i].revents == POLLIN){
						clientfd = client_array[i].fd;
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
					client_array[i].fd = -1;
				}
				client_array[i].revents = 0;
			}

			--ready;
		}
	}
	close(serverfd);

}
