#include <sys/stat.h>
#include <stdio.h>

int ftype(char* path){

	//Getting file type 
	struct stat file_stat;
	if(lstat(path,&file_stat)!=0){
		return -1;
	}
	if(S_ISREG(file_stat.st_mode)){
		return 8;
	}
	else if(S_ISLNK(file_stat.st_mode)){
		return 10;
	}
	else if(S_ISDIR(file_stat.st_mode)){
		return 4;
	}
	else{
		return 0;
	}

}

void file_type(char* path){
	
	int type = ftype(path);
	if(type==-1){
		perror("Error determining file type ");
	}
	if(type==8){
		printf("Regular ");
	}
	else if(type==10){
		printf("Softlink ");
	}
	else if(type==4){
		printf("Directory ");
	}
	else{
		printf("Other ");
	}
}

