#include "unpre.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main()
{
	int	listenfd, connfd;
	pid_t childpid;
	struct sockaddr_in cliaddr, servaddr;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(127.0.0.1);
	servaddr.sin_port = htons(SERV_PORT);
		
	bind(listenfd,(SA*)&servaddr, sizeof(servaddr));
	
		
	printf("%d\n",SERV_PORT);
	
}
