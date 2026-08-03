#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "filetype.h"
#include "fs_traverse.h"

void find(char* target,char* findpath){

	int fd,inode,count;

	fd = open(target,O_RDONLY);	
	struct stat file_stat;

	int ret = fstat(fd,&file_stat);
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

int main(int argc, char** argv){
	find(argv[1],argv[2]);
}
