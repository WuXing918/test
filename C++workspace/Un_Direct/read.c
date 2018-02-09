#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	char buf[100];
	int fd = open("wuxing.txt",O_RDONLY);
	if(fd == -1)printf("open error!\n");
	while( (read(fd,buf,100)!=0) )
	{
		printf("%s",buf);
	}
	printf("\n");
}
