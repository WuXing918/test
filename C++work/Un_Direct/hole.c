#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc,char* argv[])
{
	if(argc != 3)printf("imput error!\n"),exit(-1);
	int flag;
	int fd = open(argv[1],O_RDWR|O_CREAT,0666);
	if(fd == -1)printf("open errror!\n");
	flag = write(fd,"wuxing",sizeof("wuxing"));
	if(flag == -1)printf("write eror!\n");
	lseek(fd,1000,SEEK_SET);
	flag = write(fd,"wuxingnihao",sizeof("wuxingnihao"));
	if(flag == -1)printf("write eror!\n");
	
	

	int fdno = open(argv[2],O_RDWR|O_CREAT,0666);
	if(fdno == -1)printf("open errror!\n");
	flag = write(fdno,"wuxing",sizeof("wuxing"));
	if(flag == -1)printf("write eror!\n");
	flag = write(fdno,"wuxingnihao",sizeof("wuxingnihao"));
}
