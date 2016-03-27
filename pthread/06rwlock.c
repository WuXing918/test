/*
读写锁与互斥量相似，不过读写锁允许更高的并行性。
	互斥量要么是锁住状态，要不是不加锁状态，而且一次只有一个线程可以对其进行加锁。

读写锁有三种状态：读模式加锁，写模式加锁，不加锁。
	1.当读写锁是写加锁时，在这个锁被解索之前所有企图对它加锁的线程都将要阻塞。
	2.当读写锁是读加锁时，在这个锁被解索之前所有企图以读模式对它加锁的线程都可以获得访问权；
     以写模式加锁的线程将堵塞，并且堵塞随后的读模式加锁。这样可以避免读模式锁长期占用，导致等待
     的写模式锁请求一直得不到满足。
*/
/*
	写锁定
	pthread_rwlock_wrlock(&file_info->lock_num);
	读锁定
	pthread_rwlock_rdlock(&file_info->lock_num);
*/
#include <stdio.h>
#include <pthread.h>
struct my_file
{
	int num;
	pthread_rwlock_t lock_num;
};
void* write1(void *arg) 
{
	struct my_file *file_info = (struct my_file*)arg;
	pthread_rwlock_rdlock(&file_info->lock_num);
	printf("write1: my_file->num:%d,process:%d, thread num:%d\n",file_info->num++, getpid(),pthread_self());
	sleep(3);
	pthread_rwlock_unlock(&file_info->lock_num);
	return((void*)1);
}

void* write2(void *arg) 
{
	struct my_file *file_info = (struct my_file*)arg;
	pthread_rwlock_wrlock(&file_info->lock_num);
	printf("write2: my_file->num:%d,process:%d, thread num:%d\n",file_info->num++, getpid(),pthread_self());
	sleep(3);
	pthread_rwlock_unlock(&file_info->lock_num);
	return((void*)2);
}

int main()
{
	pthread_t th1, th2, th3;
	struct my_file *test;	
	test = (struct my_file*)malloc(sizeof(struct my_file));
	if (NULL == test) {
		perror("test malloc is failure");
		return -1;
	}
	test->num = 0;
	pthread_rwlock_init(&test->lock_num, NULL);
	int ret;
	ret = pthread_create(&th1,NULL, write1,test);
	if(0 != ret) {
		perror("pthread1 error");
		return 0;
	}
	ret = pthread_create(&th2, NULL, write2, test);
	if (0 != ret) {
		perror("pthread2 error");
		return 0;
	}
	sleep(10);	
}






