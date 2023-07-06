#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>
#include<string.h>

void stop_sig(int n){
	pause();
}

void cont_sig(int n){
}

void server_action(){
	struct sigaction act,bct,oact;
	act.sa_flags = 0;
	act.sa_handler = stop_sig;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, &oact);

	bct.sa_flags = 0;
	bct.sa_handler = cont_sig;
	sigemptyset(&bct.sa_mask);
	sigaction(SIGUSR2, &bct, NULL);
}

void out_pid(){
	int fd = open("server_config.conf", O_RDWR|O_CREAT, 0664);
	char buf[1024];
	bzero(buf, 1024);
	sprintf(buf, "%d", getpid());
	write(fd, buf, strlen(buf));
	close(fd);
}

int main(){
	server_action();
	out_pid();
	while(1){
		printf("server running..\n");
		sleep(1);
	}
}
