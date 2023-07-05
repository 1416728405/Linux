#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int main(int argc, char** argv){
	if(argc < 3)
		printf("para error\n");
	kill(atoi(argv[2]), atoi(argv[1]));
}
