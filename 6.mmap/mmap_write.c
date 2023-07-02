#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

typedef struct{
	int id;
	char data[1024];
}msg_t;

int main(){
	int fd;
	int size = 0;
	fd = open("MAP_FILE", O_RDWR);
	size = sizeof(msg_t);
	ftruncate(fd, size);

	msg_t *ptr = NULL;

	if((ptr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED){
		perror("mmap failed");
		exit(0);
	}
	close(fd);
	
	ptr->id = 0;
	bzero(ptr->data, 1024);

	while(1){
		sprintf(ptr->data, "id : %d, data : msg", ptr->id++);
		sleep(1);
	}
	
	munmap(ptr, size);
	return 0;
}



