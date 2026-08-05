#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "filetype.h"
#include "fs_traverse.h"
#include "colors.h"

void find(char* target,char* findpath){
	
	// Showing file details

	int fd,inode,count,ret;

	fd = open(target,O_RDONLY);	
	struct stat file_stat;

	if(fd == -1){
		perror(YELLOW "File not opened" RESET);
	}
	else{
		ret = fstat(fd,&file_stat);
		inode = file_stat.st_ino;
		count = file_stat.st_nlink;
		printf("File: %s\n",target);
		printf("Inode: %d\n",inode);
		printf("Link count: %d\n",count);
		printf("Type: ");
		file_type(target);
		printf("\n");
		traverse(target,inode,findpath);
	}
	close(fd);
}

int main(int argc, char** argv){
	//Getting file name and the directory to be traversed as command line arguments.
	//argv[1] is file name, argv[2] is directory
	find(argv[1],argv[2]);
}
