#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t lockA;
pthread_mutex_t lockB;

void *thread_jobA(void *arg){
	pthread_mutex_lock(&lockA);
	printf("thread 0x%x get lockA success\n", pthread_self());
	sleep(2);
	pthread_mutex_lock(&lockB);
	printf("thread 0x%x get lockB success\n", pthread_self());
	
	pthread_mutex_unlock(&lockA);
	pthread_mutex_unlock(&lockB);
}

void *thread_jobB(void *arg){
	pthread_mutex_lock(&lockB);
	printf("thread 0x%x get lockB success\n", pthread_self());
	sleep(2);
	pthread_mutex_lock(&lockA);
	printf("thread 0x%x get lockA success\n", pthread_self());
	
	pthread_mutex_unlock(&lockA);
	pthread_mutex_unlock(&lockB);

}

int main(){
	pthread_t tidA, tidB;
	pthread_create(&tidA, NULL, thread_jobA, NULL);
	pthread_create(&tidB, NULL, thread_jobB, NULL);

	while(1)
		sleep(1);

}
