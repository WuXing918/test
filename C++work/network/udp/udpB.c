#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
int main()
{
	int flag;
	int fd = socket(AF_INET,SOCK_DGRAM,0);
	if(fd == -1){
		printf("socket error\n");
		exit(-1);
	}
	printf("socket OK!\n");
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	flag = connect(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(flag == -1)
	{
		printf("connect error!\n");
		exit(-1);
	}
	printf("connect OK!\n");
	char buf[100]= "wuxingnihao!"; 
	flag = write(fd,buf,100);
	if(flag > 0)
	{
		printf("write OK\n");
	}

	
	return 0;
}
