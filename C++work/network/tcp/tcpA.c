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
	int r = bind(fd,(struct sockaddr*)&add,sizeof(add));
	if(r== -1)
	{
		printf("bind error!\n");
		exit(-1);
	}
	printf("bind OK!\n");
	
	r = listen(fd,10);
	if(r==-1)
	{
		printf("listen error!\n");
		exit(-1);
	}
	printf("listen OK!\n");

	int cfd = accept(fd,0,0);
	if(cfd == -1){
		printf("accept error!\n");
		exit(-1);
	}
	printf("accept Ok!\n");
	char buf[100];
	int len = read(cfd,buf,100);
	if(len > 10)
	{
		printf("%s\n",buf);
	}else{
		printf("read error!\n");
	}
	
	

}
