#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
static int i = 0; 
// 互斥锁
pthread_mutex_t mutex;
// 条件量
pthread_cond_t cond;

void* pthread_one(void* num)
{
	while (1) {
		pthread_mutex_lock(&mutex);
		
		if (0 == i%5) {
			pthread_cond_signal(&cond);
		} else {
			sleep(1);
			printf("pthread_one:%d\n", i++);
		}
		pthread_mutex_unlock(&mutex);
	}
}
void* pthread_two(void* num)
{
	while (1) {
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond, &mutex);
		printf("pthread_two:%d\n", i++);	
		pthread_mutex_unlock(&mutex);
	}
}

int main()
{
	// 初始化互斥锁
	pthread_mutex_init(&mutex, NULL);
	// 初始化条件量
	pthread_cond_init(&cond, NULL);
	pthread_t pfd1, pfd2;
	pthread_create(&pfd1, 0, pthread_one, NULL);
	pthread_create(&pfd2, 0, pthread_two, NULL);
	
	pthread_join(pfd1, (void**)0);
	pthread_join(pfd2, (void**)0);
}
/*
	pthread_cond_signal 发送释放互斥锁的条件量信号。


*/
