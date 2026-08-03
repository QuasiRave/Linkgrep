#include <sys/stat.h>
#include <stdio.h>

void file_type(char* path){
	struct stat file_stat;

	if(lstat(path,&file_stat)!=0){
		perror("Error determining file type ");
	}
	if(S_ISREG(file_stat.st_mode)){
		printf("Regular ");
	}
	else if(S_ISLNK(file_stat.st_mode)){
		printf("Softlink ");
	}
	else if(S_ISDIR(file_stat.st_mode)){
		printf("Directory ");
	}
	else{
		printf("Other ");
	}
}

