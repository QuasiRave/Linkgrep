#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "filetype.h"

void hardlink(char* target,int target_id,char* filepath){
	int fd,inode;
	int ret;
	fd = open(filepath,O_RDONLY);
	struct stat file_stat;
	ret = fstat(fd,&file_stat);
	inode = file_stat.st_ino;
 	
	if(inode == target_id && strcmp(filepath,target)!=0){
		file_type(filepath);
		printf("%s\n",filepath);
	}
}

void softlink(char* target,char* filepath){
	char *real_path = realpath(filepath,NULL);

	if(real_path!=NULL && strcmp(real_path,target)==0){
		if(strcmp(filepath,target)==1){
			file_type(filepath);
			printf("%s\n",filepath);
		}
	}
	free(real_path);
	real_path = NULL;
}

