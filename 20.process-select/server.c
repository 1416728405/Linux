#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<sys/socket.h>
#include<ctype.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<pthread.h>
#include<signal.h>

#define SERVER_IP "192.168.206.132"

void sig_wait(int n){
	pid_t zpid;
	while((zpid = waitpid(-1, NULL, WNOHANG)) > 0){
		printf("sig_wait zpid %d success\n", getpid());
	}
}

void *thread_wait(void *arg){
	pthread_detach(pthread_self());
	struct sigaction act,oact;
	act.sa_flags = 0;
	act.sa_handler = sig_wait;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD, &act, &oact);

	sigprocmask(SIG_SETMASK, &act.sa_mask, NULL);
	printf("wait thread ready..\n");
	while(1)
		sleep(1);
}

int main(){
	sigset_t set,oset;
	sigemptyset(&set);
	sigaddset(&set, SIGCHLD);
	sigprocmask(SIG_SETMASK, &set, &oset);

	pthread_t tid;
	pthread_create(&tid, NULL, thread_wait, NULL);

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

	pid_t pid;
	socklen_t addrlen;
	int recvlen;;
	int toupper_flag;
	struct sockaddr_in clientAddr;	
	while(1){
		addrlen = sizeof(clientAddr);
		client_fd = accept(server_fd, (struct sockaddr*)&clientAddr, &addrlen);
		if(client_fd == -1){
			perror("accept error");
			continue;
		}

		pid = fork();
		if(pid > 0){
			printf("client accept success, ip:%s, port:%d\n", inet_ntop(AF_INET, &clientAddr.sin_addr.s_addr, clientIp, 16), ntohs(clientAddr.sin_port));
			sprintf(sendBuf, "hi, <%s> welcome..\n", clientIp);
			send(client_fd, sendBuf, strlen(sendBuf), 0);
			bzero(sendBuf, 1024);		
		}else if(pid == 0){
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
			if(recvlen == 0){
				printf("user exit, process pid = %d\n", getpid());
				exit(0);
			}
		}else{
			perror("fork failed");
			exit(0);
		}


	}

	close(server_fd);
}
