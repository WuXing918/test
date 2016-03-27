#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
//线程函数
/*
	线程除了自己私有的堆栈和寄存器以外其他的都是共享的！
*/
void* pthreadone(void *num)
{
	//将本线程设置为分离线程
	pthread_detach(pthread_self());
	printf("I am pthread one!\n");
	pthread_exit("exit");
}
void* pthreadtwo(void *num)
{
	//创建的线程默认为绑定线程
	printf("I am pthread two!\n");
}
int main()
{
	pthread_t fdo;
	char* num = "传递线程的数据！\n";
	pthread_create(
			&fdo,//线程ID
			0,//线程默认属性
			pthreadone,//线程代码函数
			(void*)num//线程参数
	);
	pthread_t fdt;
	pthread_create(
		&fdt,//
		0,//
		pthreadtwo,//
		(void*)num //
	);
	char re[100];
	pthread_join(fdt, (void**)&re);
	printf("%s\n", re);
}
/*
线程分类:
1.非分离线程（pthreadtwo）
		非分离线程必须进行join回收该线程所拥有的资源（线程ID等）。
2.绑定线程（pthreadone）
	分离线程是不需要进行join的，分离线程结束的时候就会将所占有的资源进行释放。	
*/
/*	
Thread attributes:()
                   Detach state        = PTHREAD_CREATE_JOINABLE  设置分离状态
                   Scope               = PTHREAD_SCOPE_SYSTEM     设置范围
                   Inherit scheduler   = PTHREAD_INHERIT_SCHED    设置继承的调度策略
                   Scheduling policy   = SCHED_OTHER              设置调度策略
                   Scheduling priority = 0                        设置优先级
                   Guard size          = 4096 bytes               线程栈末尾的警戒缓冲区大小
                   Stack address       = 0x40196000               线程堆栈的地址
                   Stack size          = 0x201000 bytes           线程堆栈的大小
*/

