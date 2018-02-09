#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
int main(int argc,char* argv[])
{
	DIR *dir;
	struct dirent *dirent;
	dir = opendir(argv[1]);
	printf("%d\n",sizeof(dirent));
	if(dir== NULL){
		printf("open error!\n");
	}
	while((dirent = readdir(dir)) !=NULL){
		
		printf("%ld		",dirent->d_ino);
	//	printf("%d\n",dirent->d_off);
	//	printf("%f\n",dirent->d_reclen);
	//	printf("%c	",dirent->d_type);
		printf("%s\n",dirent->d_name);
	}

}
