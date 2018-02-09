#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int i;
	//
	int fd = open("my.pipe",0666);
	if(fd==-1)printf("open error!\n");	
	printf("open success!\n");
	while(1)
	{
		read(fd,&i,sizeof(i));	
		printf("%d\n",i);
	}
}
