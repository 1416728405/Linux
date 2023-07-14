#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<signal.h>
#include<errno.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<arpa/inet.h>
#include<time.h>

#define TIMEOUT 1
#define BACKLOG 128
#define EPOLLMAX 100000

int epfd;
pthread_mutex_t lock;

typedef struct{
	void *(*business)(void*);
	void *arg;
}bs_t;

typedef struct{
	int thread_shutdown;
	int thread_min;
	int thread_max;
	int thread_alive;
	int thread_busy;
	int kill_number;

	bs_t *queue;
	int max;
	int front;
	int rear;
	int cur;

	pthread_t *ctids;
	pthread_t mid;

	pthread_cond_t Not_Full;
	pthread_cond_t Not_Empty;

}pool_t;

pool_t *PTR;
pthread_t ptid;

pool_t *thread_pool_create(int Max, int Min, int QMax);

int Producer_add_task(pool_t *p, bs_t bs);

void *Customer_thread(void *arg);

void *Manager_thread(void *arg);

int thread_pool_destroy(pool_t *p);

void *user_business(void *arg);

int if_thread_alive(pthread_t tid);

int thread_pool_destroy(pool_t *ptr);

int Net_init();

int Epoll_create(int sockfd);

int Epoll_Listen(int sockfd, pool_t *ptr);

void *Business_Accept(void *arg);

void *Business_Retime(void *arg);

void *print_thread(void *arg);

void sig_usr(int n);
