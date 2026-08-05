#include <linux/limits.h>
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include "link_probe.h"
#include "colors.h"

void traverse(char* target,int target_id,char* dirpath){

	//Traversing the file system
	DIR *dirptr;
	struct dirent *dir;
	dirptr = opendir(dirpath);
	
	char filepath[PATH_MAX];
	

	if(dirptr==NULL){
		printf(RED "Error opening directory %s\n" RESET,dirpath);
		perror("\t");
	}
	else{
		while((dir = readdir(dirptr))!=NULL){
			if(strcmp(dir->d_name,".")==0 || strcmp(dir->d_name,"..")==0){
				continue;
			}
			else{
				if(strcmp(dirpath,"/")==0){
					snprintf(filepath,sizeof(filepath),"%s%s",dirpath,dir->d_name);
				}
				else{
					snprintf(filepath,sizeof(filepath),"%s/%s",dirpath,dir->d_name);
				}
				
				if(dir->d_type == DT_LNK){
					softlink(target,filepath);
					
				}

				hardlink(target,target_id,filepath);


				if(dir->d_type == DT_DIR){
					traverse(target,target_id,filepath);
				}

			}
		}
	}
	closedir(dirptr);
	dirptr = NULL;
}

