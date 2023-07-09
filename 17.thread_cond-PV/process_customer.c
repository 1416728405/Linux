#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>


pthread_mutex_t lock;
pthread_cond_t Not_Full;
pthread_cond_t Not_Empty;


typedef struct{
	int id;
	char desc[1024];
}data_t;

typedef struct{
	data_t *container;
	int Max;
	int Front;
	int Rear;
	int Cur;
}queue_t;

queue_t* createContainer(int nMax){
	queue_t *ct = (queue_t*)malloc(sizeof(queue_t));
	ct->container = (data_t*)malloc(sizeof(data_t) * nMax);

	ct->Max = nMax;
	ct->Front = 0;
	ct->Rear = 0;
	ct->Cur = 0;
}

void *customer_thread(void *arg){
	queue_t *ct = (queue_t*) arg;
	data_t data;
	while(1){
		pthread_mutex_lock(&lock);
		while(ct->Cur == 0){
			pthread_cond_wait(&Not_Empty, &lock);

		}
		data = ct->container[ct->Rear];
		ct->Rear = (ct->Rear + 1) % ct->Max;
		--(ct->Cur);
		pthread_mutex_unlock(&lock);
		printf("customer thread 0x%x get data success, id = %d, desc = %s\n", (unsigned int)pthread_self(), data.id, data.desc);
		pthread_cond_signal(&Not_Full);
	}
	pthread_exit(0);
}

int main(){
	pthread_t tid[3];
	queue_t *ct = createContainer(50);
	if(pthread_mutex_init(&lock, NULL) != 0 || pthread_cond_init(&Not_Empty, NULL) != 0
			|| pthread_cond_init(&Not_Full, NULL) != 0){
		printf("init failed\n");
		exit(0);
	}

	for(int i = 0; i < 3; i++){
		pthread_create(&tid[i], NULL, customer_thread, (void*)ct);
	}
	
	data_t node;
	for(int i = 0; i < 20; i++){
		node.id = i;
		sprintf(node.desc, "desc:nod.id=%d", i);
		
		pthread_mutex_lock(&lock);
		ct->container[ct->Front] = node;
		ct->Front = (ct->Front + 1) % ct->Max;
		(ct->Cur)++;
		pthread_mutex_unlock(&lock);
		printf("produce tid 0x%x push data success\n", (unsigned int)pthread_self());
		pthread_cond_signal(&Not_Empty);
	}

	while(1)
		sleep(1);

	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&Not_Empty);
	pthread_cond_destroy(&Not_Full);
}
