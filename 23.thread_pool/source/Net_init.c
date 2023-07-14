#include<server.h>

int Net_init(){
	int serverfd;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if((serverfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("Net_init error, socket error");
		exit(0);
	}

	if(bind(serverfd, (struct sockaddr*)&addr, sizeof(addr)) == -1){
		perror("Net_init error, bind error");
		exit(0);
	}
	
	listen(serverfd, BACKLOG);
	
	return serverfd;
}
