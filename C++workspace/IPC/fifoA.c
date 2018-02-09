#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	// create pipe
	int r = mkfifo("my.pipe",0666);
	if(r==-1)printf("mkfifo error!\n");
	int fd = open("my.pipe",O_RDWR);
	if(fd ==-1)printf("open pipe error!\n");
	printf("open success!\n");
	int i=1;
	sleep(10);
	while(i++<20)
	{
		r = write(fd,&i,sizeof(i));	
		if(r==-1)printf("write error!\n");
	}
	system("rm my.pipe");
}
