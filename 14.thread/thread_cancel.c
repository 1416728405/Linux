#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>

void *thread_job(void* arg){
	//printf("thread arg %d\n", *(int *)arg);
	while(1){
		//sleep(1);
		pthread_testcancel();
	}
	return (void*)10;
}

int main(){
	int arg = 1024;
	pthread_t tid;
	int err;
	err = pthread_create(&tid, NULL, thread_job, (void*)&arg);
	if(err != 0){
		printf("pthread_create failed:%s\n", strerror(err));
	}
	sleep(3);
	void *value = NULL;
	pthread_cancel(tid);
	pthread_join(tid, &value);
	printf("pthread_cancle exit code is %ld\n",(long int) value);
}
