#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

void *thread_job(void *arg){
}

int main(){
	pthread_attr_t attr;
	void *stack_addr;
	size_t stack_size;
	int thread_state;

	pthread_attr_init(&attr);
	pthread_attr_getdetachstate(&attr, &thread_state);
	if(thread_state == PTHREAD_CREATE_DETACHED){
		printf("thread_state = detach\n");
	}else{
		printf("thread_state = join\n");
	}

	pthread_attr_getstack(&attr, &stack_addr, &stack_size);
	printf("stack_addr = %p, stack_size = %d\n", stack_addr, (unsigned int)stack_size);
	
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	stack_size = 0x100000;

	int flag = 0;
	pthread_t tid;
	int err;
	while(1){
		stack_addr = malloc(stack_size);
		pthread_attr_setstack(&attr, stack_addr, stack_size);
		err = pthread_create(&tid, &attr, thread_job, NULL);
		if(err > 0){
			printf("pthread create failed : %s\n", strerror(err));
			exit(0);
		}
		printf("%d\n", ++flag);
	}

	pthread_attr_destroy(&attr);
}
