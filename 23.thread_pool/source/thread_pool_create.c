#include<server.h>

pool_t *thread_pool_create(int Max, int Min, int QMax){
	pool_t *ptr = NULL;
	if((ptr = (pool_t*)malloc(sizeof(pool_t))) == NULL){
		perror("thread_pool_create, pool_t malloc failed");
		exit(0);
	}
	ptr->thread_shutdown = 1;
	ptr->thread_min = Min;
	ptr->thread_max = Max;
	ptr->thread_alive = 0;
	ptr->thread_busy = 0;
	ptr->kill_number = 0;

	if((ptr->queue = (bs_t*)malloc(sizeof(bs_t) * QMax)) == NULL){
		perror("thread_pool_create, queue malloc failed");
		exit(0);
	}

	ptr->max = QMax;
	ptr->front = 0;
	ptr->rear = 0;
	ptr->cur = 0;

	if((ptr->ctids = (pthread_t*)malloc(sizeof(pthread_t) * Max)) == NULL){
		perror("thread_pool_create, ctids malloc failed");
		exit(0);
	}
	bzero(ptr->ctids, sizeof(pthread_t) * Max);

	int err;
	for(int i = 0; i < Min; i++){
		if((err = pthread_create(&ptr->ctids[i], NULL, Customer_thread, (void*)ptr)) > 0){
			printf("thread_pool_create, customer thread create error:%s\n", strerror(err));
			exit(0);
		}
		++ptr->thread_alive;
	}
	
	if((err = pthread_create(&ptr->mid, NULL, Manager_thread, (void*)ptr)) > 0){
			printf("thread_pool_create, manager thread create error:%s\n", strerror(err));
			exit(0);
	}

	if(pthread_cond_init(&ptr->Not_Full, NULL) != 0 || pthread_cond_init(&ptr->Not_Empty, NULL) != 0 || pthread_mutex_init(&lock, NULL) != 0){
		printf("thread_pool_create, init cond failed");
		exit(0);
	}

	pthread_create(&ptid, NULL, print_thread, (void*)ptr);

	return ptr;

}
