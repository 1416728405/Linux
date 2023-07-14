#include<server.h>

void *Customer_thread(void *arg){
	pool_t *p = (pool_t *)arg;
	bs_t bs;
	pthread_detach(pthread_self());

	while(p->thread_shutdown){
		pthread_mutex_lock(&lock);
		while(p->cur == 0){
			pthread_cond_wait(&p->Not_Empty, &lock);
			if(p->thread_shutdown == 0){
				pthread_mutex_unlock(&lock);
				printf("Customer_thread, Main thread exit,Customer thread[0x%x] exit..\n", (unsigned int)pthread_self());
				pthread_exit(0);
			}
			if(p->kill_number != 0){
				if(p->kill_number-1 == 0)
					pthread_kill(ptid, SIGUSR1);
				--p->thread_alive;
				--p->kill_number;
				printf("customer_thread [0x%x]exit, kill_number %d\n", (unsigned int)pthread_self(), p->kill_number);
				pthread_mutex_unlock(&lock);
				pthread_exit(0);

			}
		}
		bs.business = p->queue[p->rear].business;
		bs.arg = p->queue[p->rear].arg;
		p->rear = (p->rear + 1) % p->max;
		--(p->cur);
		++(p->thread_busy);
		pthread_kill(ptid, SIGUSR1);
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&p->Not_Full);
		
		printf("Customer thread[0x%x] get business addr[%p]\n", (unsigned int)pthread_self(), bs.business);
		bs.business(bs.arg);
		
		pthread_mutex_lock(&lock);
		--(p->thread_busy);
		pthread_kill(ptid, SIGUSR1);
		pthread_mutex_unlock(&lock);
	}

	pthread_exit(0);
}
