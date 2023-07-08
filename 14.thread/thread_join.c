#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

void *thread_job(void *arg){
	printf("thread create\n");
	return (void*)10;
}


int main(){
	pthread_t tid;
	pthread_create(&tid, NULL, thread_job, NULL);
	void *reval = NULL;
	pthread_join(tid, &reval);
	printf("exit code = %ld\n", (long int)reval);
}
