#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "filetype.h"
#include "fs_traverse.h"
#include "link_probe.h"
#include "colors.h"

#define VERSION "linkgrep 1.0.2"
#define UNDERLINE "\033[4m"
#define ITALIC "\033[3m"
#define FONT_RESET "\033[0m"


int show(char* target,char* findpath){
	
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
	}
	close(fd);
	return inode;
}

void find(char* target,char* findpath){
	int inode = show(target,findpath);
	traverse(target,inode,findpath);
}

void help(){
	
	printf("Linkgrep is a simple Linux command-line tool for exploring file relationships\n\n");

	printf(UNDERLINE "Usage\t" FONT_RESET);
	printf("linkgrep");
	printf(ITALIC " <?options>\n\n" FONT_RESET);

	printf(UNDERLINE "Options\n" FONT_RESET);

	printf("-%c\t\t\t\tShow this help\n",'h');
	printf("-%c\t\t\t\tShow version\n",'v');
	printf("-%c %s %s\t\tSearching alternative links for a file within a directory\n",'f',"filename","directory");
	printf("-%c %s\t\t\tFinding real path of a softlink\n\n",'l',"softlink");
	


	printf("For more, please visit:\n\t<https://github.com/QuasiRave/Linkgrep>\n");
}

void version(){
	printf("%s\n",VERSION);
}

int main(int argc, char** argv){
	//Geting options and filenames as commandline arguments
	int opt;
	if(argc==1){
		help();
	}

	while((opt=getopt(argc,argv,"if:flhv"))!=-1){
		switch(opt){
			case 'f':
				find(argv[2],argv[3]);
				break;
			case 'l':
				if(ftype(argv[2])== 10){
					softlink(argv[2]);
				}
				else{
					puts("Not a softlink or file not found");
				}
				break;
			case 'h':
				help();
				break;
			case 'v':
				version();
				break;
			case '?':
				puts("Try 'linkgrep -h' ");
		}
	}
}
