#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
int main(int argc,char**argv)
{
	if(argc!=2)
	{
		printf("请输入主机名或者ip地址！\n");
	return;
	}
	struct hostent *host = gethostbyname(argv[1]);
	if(host)
	{
		printf("host_name = %s\n",host->h_name);
		printf("host_ipty = %d\n",host->h_addrtype);
		printf("host_addr = %s\n",host->h_addr);
		printf("host_adth = %d\n",host->h_length);
		
	}else{
		printf("获取失败！\n");
		return;
	}
}
