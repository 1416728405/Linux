#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

int num;
pthread_mutex_t lock;

void *thread_job(void* arg){
	pthread_detach(pthread_self());
	for(int i = 0; i < 5000; i++){
		pthread_mutex_lock(&lock);
		printf("num:%d\n", ++num);
		pthread_mutex_unlock(&lock);
	}
}

int main(){
	pthread_mutex_init(&lock, NULL);
	pthread_t tid;
	pthread_create(&tid, NULL, thread_job, NULL);
	pthread_create(&tid, NULL, thread_job, NULL);
	while(1)
		sleep(1);

	pthread_mutex_destroy(&lock);
}
