#include<server.h>

int Producer_add_task(pool_t *p, bs_t bs){
	if(p->thread_shutdown){
		pthread_mutex_lock(&lock);
		while(p->cur == p->max){
			pthread_cond_wait(&p->Not_Full, &lock);
			if(p->thread_shutdown == 0){
				pthread_mutex_unlock(&lock);
				printf("Producer_add_task, thread_shutdown = 0\n");
				pthread_exit(0);
			}
		}
		p->queue[p->front].business = bs.business;
		p->queue[p->front].arg = bs.arg;
		p->front = (p->front + 1) % p->max;
		++(p->cur);

		pthread_mutex_unlock(&lock);

		pthread_cond_signal(&p->Not_Empty);
	}else{
		pthread_exit(NULL);
	}

	return 0;
}
