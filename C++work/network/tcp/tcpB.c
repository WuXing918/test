#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main()
{
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1)
	{
		printf("socket erro\nr");
		exit(-1);
	}
	printf("socket oK!\n");
	struct sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_port = htons(8888);
	add.sin_addr.s_addr = inet_addr("127.0.0.1");
	int r = connect(fd,(struct sockaddr*)&add,sizeof(add));
	if(r== -1)
	{
		printf("connect error!\n");
		exit(-1);
	}
	printf("connect OK!\n");
	
	char buf[100] = "wuxingnihao!";
	int len = write(fd,buf,100);
	if(len > 10)
	{
		printf("write OK");
	}else{
		printf("write error!\n");
	}
	
	

}
