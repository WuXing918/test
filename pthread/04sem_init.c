#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
//定义信号量
sem_t bin_sem;
void *pthread_one(void *num)
{
	//等待信号量资源，如果信号量资源没有 即bin_sem为0 那么就会阻塞等待资源。
	printf("pthread_one: sem wait start!\n");
	sem_wait(&bin_sem);
	printf("pthread_one: sem wait end!\n");
}
void *pthread_two(void *num)
{
	//增加信号量资源(+1)
	printf("pthread_two: sem post start!\n");
	sem_post(&bin_sem);
	printf("pthread_two: sem post end!\n");
}
int main()
{
	
	int res;
	//初始化信号量资源。
	sem_init(&bin_sem, 0, 0);
	if (res != 0)
	{
		printf("init sem err\n");
		return -1;
	}

	pthread_t one_pthread;
	pthread_t two_pthread;
	pthread_create(&one_pthread, 0, pthread_one, NULL);
	sleep(5);
	pthread_create(&two_pthread, 0, pthread_two, NULL);
	pthread_join(one_pthread, (void**)0);
	pthread_join(two_pthread, (void**)0);
}
/*
	sem_init()  初始化信号量资源
	sem_post()  增加信号量资源
	sem_wait()  等待信号量资源
	sem_timedwait() 等待信号量资源超时
	sem_destroy()   释放信号量资源
*/
