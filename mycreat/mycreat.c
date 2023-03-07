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
	
	fd = /*	[1] fill out here using system call  */;
	
    //write_size=write( /* [2] fill out here : write argument */ );
    //error handling
	
    printf("write to file %s write size %d\n", fname, write_size);
	/* [3] fill out here : */ 
}

