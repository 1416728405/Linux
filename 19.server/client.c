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

	if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket error");
		exit(0);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);;
	
	if(connect(client_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1){
		perror("connect error");
		exit(0);
	}
	
	recv(client_fd, recvBuf, sizeof(recvBuf), 0);
	printf("%s", recvBuf);
	bzero(recvBuf, 1024);

	while(fgets(sendBuf, sizeof(sendBuf), stdin) != NULL){
		send(client_fd, sendBuf, strlen(sendBuf), 0);
		bzero(sendBuf, 1024);
		recv(client_fd, recvBuf, sizeof(recvBuf), 0);
		printf("%s", recvBuf);
		bzero(recvBuf, 1024);
	}
	

	close(client_fd);
	

}
