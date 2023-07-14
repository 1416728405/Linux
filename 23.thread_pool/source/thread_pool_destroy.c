#include<server.h>

int thread_pool_destroy(pool_t *ptr){
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&ptr->Not_Full);
	pthread_cond_destroy(&ptr->Not_Empty);

	free(ptr->ctids);
	free(ptr->queue);
	free(ptr);
}
