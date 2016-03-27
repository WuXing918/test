#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int i = 0;
int j = 0;
//互斥锁
pthread_mutex_t m;
//条件量
// pthread_cond_t cond;
void handle(void *d)
{
	printf("退出后的调用!\n");
	pthread_mutex_unlock(&m);
}
void* pthread_add1(void *num)
{
	while(1){
		pthread_cleanup_push(handle,NULL/*这个NULL为互斥锁属性，NULL指的是省略互斥锁属性*/);
		pthread_mutex_lock(&m);
		i++;
		j++;
		//if(i!=j)
		printf("线程one：i:%dj:%d\n",i,j);
		pthread_cleanup_pop(NULL);
		pthread_mutex_unlock(&m);
		sleep(1);
	}
}
void* pthread_add2(void *num)
{
	while(1){	
		pthread_cleanup_push(handle,NULL);
		pthread_mutex_lock(&m);
		i++;
		j++;
		//if(i!=j)
		printf("线程two：i:%dj:%d\n",i,j);
		//内部推出线程！
		pthread_exit((void*)0);
		pthread_cleanup_pop(NULL);
		pthread_mutex_unlock(&m);
		sleep(1);	
	}
}
int main()
{
	pthread_t pfd1,pfd2;
	pthread_mutex_init(&m,NULL);
	
	pthread_create(&pfd1,0,pthread_add1,"I am one!");
	pthread_create(&pfd2,0,pthread_add2,"I am two!");
	
	pthread_join(pfd1,(void**)0);
	pthread_join(pfd2,(void**)0);
}
/*
	pthread_mutex_*：
		 为互斥锁/互斥量，进行共享资源互斥访问！
	在使用互斥量进行共享资源访问的时候如果在没有打开互斥锁而该
	线程终止,而其他线程一直在等待该锁打开,那么就会导致死锁！
	解决办法：
		pthread_cleanup_push();pthread_cleanup_pop();	
*/
/*

*/
