#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include "link_probe.h"

void traverse(char* target,int target_id,char* dirpath){

	DIR *dirptr;
	struct dirent *dir;
	dirptr = opendir(dirpath);

	char filepath[256];

	if(dirptr==NULL){
		perror("Error opening directory ");
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
				
				softlink(target,filepath);
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

