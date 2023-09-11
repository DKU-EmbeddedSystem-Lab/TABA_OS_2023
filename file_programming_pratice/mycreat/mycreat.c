#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_BUF 64
char fname[] ="newfile";
char dummy[] ="TABA OS 2023 [your name here]\n";
int main(int argc, char *argv[]){
	//변수 선언
	int fd, read_size, write_size =0;
	char buf[MAX_BUF];
	
	fd = open(fname, O_RDWR|O_CREAT|O_TRUNC, 0664);
	
    write_size=write(fd, dummy, sizeof(dummy));
    //error handling
    printf("write to file %s write size %d\n", fname, write_size);
	close(fd);
}

