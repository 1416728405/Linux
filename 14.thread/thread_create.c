#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

void *thread_job(void* arg){
	//printf("thread arg %d\n", *(int *)arg);
	while(1)
		sleep(1);
}

int main(){
	int arg = 1024;
	pthread_t tid;
	int flag = 1;
	while(1){
		int err;
		err = pthread_create(&tid, NULL, thread_job, (void*)&arg);
		if(err != 0){
			printf("pthread_create failed:%s\n", strerror(err));
			break;
		}
		printf("%d\n", flag++);
	}
}
