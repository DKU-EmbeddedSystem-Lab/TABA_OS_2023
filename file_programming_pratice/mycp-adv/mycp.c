#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 64

int main(int argc, char *argv[]){

	int fd_origin, fd_dest, read_size, write_size =0;
	char buf[MAX_BUF];

	struct stat *stat_origin=(struct stat *)malloc(sizeof(struct stat));
	mode_t flag_origin;

	if (argc!=3){
		printf("USAGE: %s origin dest\n",argv[0]);
		exit(-1);	}
	fd_origin 	= open(argv[1], O_RDONLY);
	
    /*TODO [1] fall through. get file attribute structure from fd_origin */
    
    flag_origin = /*TODO [2] */;
    /* fall through. let's get member from struct stat "stat_origin.some_field_here" see man fstat */;
	


    //read and write file
    printf("flag origin %o \n",flag_origin);
    fd_dest	= open(argv[2], O_RDWR|O_CREAT|O_SYNC, flag_origin);
	//open error handling
	//read from the origin file
	while((read_size = read(fd_origin, buf, MAX_BUF))!= 0){
		 //write to the dest file
		write_size = write(fd_dest, buf, read_size);
	}
	close(fd_origin); close(fd_dest);
}

