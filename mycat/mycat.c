#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 64

int main(int argc, char *argv[]){
	//변수 선언
	int fd, read_size, write_size =0;
	char buf[MAX_BUF];
	//예외 처리
	if (argc!=2){
		printf("USAGE: %s newfile\n",argv[0]);
		exit(-1);
	}
	//fd = /*	TODO [1] fill out here using system call  */;
	if (fd < 0){
		//open error handling
		perror("fd open error\n");
	}
	//while((read_size = /* TODO [2] fall through. fill out here using syscall. */) != 0){
        //printf("%s",buf);
		//write_size = /* TODO [3] fall through. fill out here using syscall. */;
    }
	/*TODO [4] fall through. fd must be closed. */;
}

