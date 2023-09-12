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
	fd = open(argv[1], O_RDONLY);
	if (fd < 0){
		//open error handling
		perror("fd open error\n");
	}
	while((read_size = read(fd, buf, MAX_BUF)) != 0){
        //printf("%s",buf);
		write_size = write(STDOUT_FILENO, buf, read_size);
    }
	close(fd);
}

