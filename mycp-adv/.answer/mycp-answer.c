#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 64

int main(int argc, char *argv[]){
	//변수 선언
	int fd_origin, fd_dest, read_size, write_size =0;
	char buf[MAX_BUF];
	struct stat stat_origin;
	mode_t flag_origin;
	
	//예외 처리
	if (argc!=3){
		printf("USAGE: %s origin dest\n",argv[0]);
		exit(-1);	}
	fd_origin 	= open(argv[1], O_RDONLY|O_SYNC);


	/*TODO [1] fall through. get file attribute structure from fd_origin */
    fstat(fd_origin, &stat_origin);
    if(&stat_origin==NULL){printf("NULL pointer error stat_origin\n");}
	
    flag_origin = stat_origin.st_mode;/*TODO [2] fall through. let's get member from struct stat "stat_origin->field_here" */	
    printf("flag_origin %o\n", flag_origin);


    fd_dest	= open(argv[2], O_RDWR|O_CREAT|O_SYNC, flag_origin);
    if(fd_dest < -1){perror("error while opening dest\n");}
	//open error handling
	//read from the origin file
	while((read_size = read(fd_origin, buf, MAX_BUF))!= 0){
		 //write to the dest file
		 write_size=write(fd_dest, buf, read_size);
	}
	close(fd_origin); close(fd_dest);
}

