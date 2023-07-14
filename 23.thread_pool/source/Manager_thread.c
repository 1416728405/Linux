#include<server.h>

void *Manager_thread(void *arg){
	pool_t *ptr = (pool_t*)arg;
	pthread_detach(pthread_self());
	int cur, busy, alive;

	while(ptr->thread_shutdown){
		pthread_mutex_lock(&lock);
		cur = ptr->cur;
		busy = ptr->thread_busy;
		alive = ptr->thread_alive;
		pthread_mutex_unlock(&lock);

		if((cur > alive-busy || (double)busy / alive * 100 > 70) && alive + ptr->thread_min <= ptr->thread_max){
			for(int flag = 0, add = 0; add < ptr->thread_min && flag < ptr->thread_max; flag++){
				if(ptr->ctids[flag] == 0 || !if_thread_alive(ptr->ctids[flag])){
					pthread_create(&ptr->ctids[flag], NULL, Customer_thread, (void*)ptr);
					pthread_mutex_lock(&lock);
					++(ptr->thread_alive);
					pthread_mutex_unlock(&lock);
					add++;
				}
			}
			pthread_kill(ptid, SIGUSR1);
		}

		if((busy * 2 <= alive - busy) && alive - ptr->thread_min >= ptr->thread_min){
			pthread_mutex_lock(&lock);
			ptr->kill_number = ptr->thread_min;
			pthread_mutex_unlock(&lock);
			for(int i = 0; i < ptr->thread_min; i++){
				pthread_cond_signal(&ptr->Not_Empty);
			}
		}

		sleep(TIMEOUT);
	}
}
