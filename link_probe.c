#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "filetype.h"
#include "colors.h"


void hardlink(char* target,int target_id,char* filepath){

	//Looking for links for the file and target file for the links
	int fd,inode;
	int ret;
	struct stat file_stat;
	fd = open(filepath,O_RDONLY);
	
	if(fd == -1){
		printf(RED "Error opening file %s\n" RESET,filepath);
		perror("\t");
	}

	ret = fstat(fd,&file_stat);
	inode = file_stat.st_ino;
 	
	if(inode == target_id && strcmp(filepath,target)!=0){
		file_type(filepath);
		printf("%s\n",filepath);
	}
	close(fd);
}

void softlink(char* target,char* filepath){

	//Looking for absolute path
	char *real_path;
	real_path = realpath(filepath,NULL);
	
	if(real_path!=NULL && strcmp(real_path,target)==0){
		if(strcmp(filepath,target)==1){
			file_type(filepath);
			printf("%s\n",filepath);
		}
	}
	free(real_path);
	real_path = NULL;
}

