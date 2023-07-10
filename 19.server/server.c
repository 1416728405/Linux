#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<sys/socket.h>
#include<ctype.h>
#include<arpa/inet.h>


#define SERVER_IP "192.168.206.132"


int main(){
	int server_fd, client_fd;
	time_t tp;
	char time_buf[1024];
	char sendBuf[1024];
	char recvBuf[1024];
	char clientIp[16];

	bzero(time_buf, 1024);
	bzero(sendBuf, 1024);
	bzero(recvBuf, 1024);
	bzero(clientIp, 1024);

	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket error");
		exit(0);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1){
		perror("bind error");
		exit(0);
	}

	if(listen(server_fd, 128) == -1){
		perror("listen error");
		exit(0);
	}

	socklen_t addrlen;
	int recvlen;;
	int toupper_flag;
	struct sockaddr_in clientAddr;	
	while(1){
		addrlen = sizeof(clientAddr);
		client_fd = accept(server_fd, (struct sockaddr*)&clientAddr, &addrlen);

		printf("client accept success, ip:%s, port:%d\n", inet_ntop(AF_INET, &clientAddr.sin_addr.s_addr, clientIp, 16), ntohs(clientAddr.sin_port));
		sprintf(sendBuf, "hi, <%s> welcome..\n", clientIp);
		send(client_fd, sendBuf, strlen(sendBuf), 0);
		bzero(sendBuf, 1024);		
		while((recvlen = recv(client_fd, recvBuf, sizeof(recvBuf), 0)) > 0){
			if(strcmp(recvBuf, "localtime\n") == 0){
				tp = time(NULL);
				ctime_r(&tp, time_buf);
				send(client_fd, time_buf, strlen(time_buf), 0);
				bzero(time_buf, 1024);
			}else{
				send(client_fd, recvBuf, strlen(recvBuf), 0);
			}
			bzero(recvBuf, 1024);

		}

		close(client_fd);
	}

	close(server_fd);
}
