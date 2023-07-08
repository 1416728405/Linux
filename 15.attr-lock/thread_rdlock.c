#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

int num;
pthread_rwlock_t lock;

void *thread_wr(void *arg){
	while(1){
		pthread_rwlock_wrlock(&lock);
		printf("thread_wr 0x%x, write num %d\n",(unsigned int) pthread_self(), num++);
		pthread_rwlock_unlock(&lock);
		usleep(100000);
	}
}

void *thread_rd(void *arg){
	while(1){
		pthread_rwlock_rdlock(&lock);
		printf("thread_wr 0x%x, read num %d\n",(unsigned int) pthread_self(), num);
		pthread_rwlock_unlock(&lock);
		usleep(100000);
	}

}


int main(){
	pthread_rwlock_init(&lock, NULL);
	pthread_t tid[8];
	for(int i = 0; i < 3; i++){
		pthread_create(&tid[i], NULL, thread_wr, NULL);
	}
	for(int i = 3; i < 8; i++){
		pthread_create(&tid[i], NULL, thread_rd, NULL);
	}
	while(1)
		sleep(1);
	pthread_rwlock_destroy(&lock);
}
