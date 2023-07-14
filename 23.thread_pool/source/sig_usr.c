#include<server.h>

void sig_usr(int n){
	printf("thread_poll info:[alive]%d [Busy]%d, [Idel]%d, [Cur]%d [B/A]%.2f%%, [A/M]%.2f%%\n", PTR->thread_alive, PTR->thread_busy,  PTR->thread_alive-PTR->thread_busy, PTR->cur, (double)PTR->thread_busy/PTR->thread_alive * 100, (double)PTR->thread_alive/PTR->thread_max * 100);
}
