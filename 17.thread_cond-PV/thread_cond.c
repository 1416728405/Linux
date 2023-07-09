#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

int day_night;
pthread_mutex_t lock;
pthread_cond_t cd;

void *thread_A(void *arg){
	while(1){
		pthread_mutex_lock(&lock);
		while(day_night == 0){
			pthread_cond_wait(&cd, &lock);
		}
		printf("thread_A 0x%x day %d\n", (unsigned int)pthread_self(), day_night--);
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cd);
		//sleep(1);
	}
}

void *thread_B(void *arg){
	while(1){
		pthread_mutex_lock(&lock);
		while(day_night == 1){
			pthread_cond_wait(&cd, &lock);
		}
		printf("thread_B 0x%x day %d\n", (unsigned int)pthread_self(), day_night++);
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cd);
		//sleep(1);
	}
}

int main(){
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&cd, NULL);

	pthread_t tidA, tidB;
	pthread_create(&tidA, NULL, thread_A, NULL);
	pthread_create(&tidB, NULL, thread_B, NULL);

	while(1)
		sleep(1);

	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cd);
}
