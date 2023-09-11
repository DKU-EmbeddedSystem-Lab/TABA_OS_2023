#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 64

int main(int argc, char *argv[]){
	//변수 선언
	int fd_origin, fd_dest, read_size, write_size =0;
	char buf[MAX_BUF];
	//예외 처리
    if (argc!=3){
		printf("USAGE: %s origin dest\n",argv[0]);
		exit(-1);
	}
	fd_origin = open(argv[1], O_RDONLY);
	fd_dest = open(argv[2], O_RDWR|O_CREAT|O_SYNC, 0664);
	//fd_dest = open(argv[2], O_RDWR|O_CREAT|O_SYNC|O_EXCL, 0664);

	if (fd_origin < 0 || fd_dest <0){
		//open error handling
		perror("fd open error\n");
	}

	//read from the origin file
	while((read_size = read(fd_origin, buf, MAX_BUF))!= 0){
        //write to the dest file
		//printf("loop count read_size%d\n",read_size);
		write_size = write(fd_dest, buf, read_size);
	}
	close(fd_dest);
    close(fd_origin);
}

