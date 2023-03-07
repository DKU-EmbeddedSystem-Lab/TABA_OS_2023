#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 64

int main(int argc, char *argv[]){

	int fd_origin, fd_dest, read_size, write_size =0;
	char buf[MAX_BUF];
	
    if (argc!=3){
		printf("USAGE: %s origin dest\n",argv[0]);
		exit(-1);
	}
	//fd_origin = /*	TODO    [1] fill out here using system call  */;
	//fd_dest = /*    TODO	[1-1] fill out here using system call*/;

	if (fd_origin < 0 || fd_dest <0){
		//open error handling
		perror("fd open error\n");
	}

	//read from the origin file
	while((read_size = /*TODO [2] fill out here using system call. read origin file*/)!= 0){
        //write to the dest file
		write_size = /*TODO [3] fill out here using system call. write to dest file*/;
	}
	close(fd_dest);
    close(fd_origin);
}

