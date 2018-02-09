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
	//the struct must be init!	头文件为 netinet/in.h 必须声明
	struct sockaddr_in ad = {0};
	int fd = socket(AF_INET,SOCK_DGRAM,0);
	if(fd == -1){
		printf("socket error\n");
		exit(-1);
	}
	printf("socket OK!\n");
	
	ad.sin_family = AF_INET;
	ad.sin_port = htons(9999);
	ad.sin_addr.s_addr = inet_addr("127.0.0.1");  
	flag = bind(fd,(struct sockaddr*)&ad,sizeof(ad));
	if(flag == -1)
	{
		printf("bind error!\n");
		exit(-1);
	}
	printf("bind OK!\n");
	while(1){
	
		char buf[20];
		bzero(buf,20);
		flag = recv(fd,buf,20,MSG_WAITALL);
		if(flag > 0)
		{
			printf("%s\n",buf);	
		}else
		{
			printf("read error\n");
		}
	}	
	return 0;
}
/*
	
*/
