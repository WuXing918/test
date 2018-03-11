#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
//  signal deal function信号处理函数 
void deal(int s)
{
	printf("start deal!\n");
	printf("process is %d\n",s);
	printf("huishouzijincheng fanhuizhi !\n");
	int status;
	wait(&status);
	printf("%d\n",WEXITSTATUS(status));
	printf("deal end!\n");

}
int main()
{
	int pid;
	printf("before process init \n");
	pid = fork();
	if(pid == 0)
	{
		printf("process\n");	
		sleep(1);
		printf("pocess end!\n");
	}else
	{
		//信号与信号处理函数绑定
		signal(SIGCHLD,deal);
		sleep(3);
		printf("parent process!\n");
	}
}

/*SIGNAL 信号是子进程先结束，而父进程后结束，
  那么子进程将变成僵尸进程，僵尸进程是必须回收的。
*/
