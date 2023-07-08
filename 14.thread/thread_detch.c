#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

void *thread_job(void *arg){
	pthread_detach(pthread_self());
	printf("thread tid %x create\n", (unsigned int)pthread_self());
	return (void*)10;
}


int main(){
	pthread_t tid;
	pthread_create(&tid, NULL, thread_job, NULL);
	void *reval = NULL;
	//pthread_join(tid, &reval);
	//printf("exit code = %ld\n", (long int)reval);
	while(1)
		sleep(1);
}
