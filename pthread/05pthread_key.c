#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
/*
	线程私有数据
*/
// 全局变量
pthread_key_t key;
void handle(void* data)
{
	if(data != NULL)
		free (data);
		printf("Thread (%u) free key\n", (unsigned)pthread_self());

}
void print_key(void)  
{            
	char *p;            
	p = (char *)pthread_getspecific(key); 
    printf("pthread_one(%u) key_value:%s\n", (unsigned)pthread_self(), p);
}


void *pthread_one(void *num)
{
	printf("pthread_one(%u): start\n", (unsigned)pthread_self());
	char * p = malloc(7*sizeof(char)); 
    memset(p, 'a', 6);  
    p[6] = '\0';
	printf("pthread_one(%u) p:%s\n",(unsigned)pthread_self(),p);   
    pthread_setspecific(key, p); 
    print_key();
	printf("pthread_one(%u): end\n", (unsigned)pthread_self());
}

int main()
{
	pthread_key_create(&key, handle);
	pthread_t t1;
	pthread_create(&t1, 0, pthread_one, NULL);
	sleep(5);
	printf("pthread_main(%u):%s\n",(unsigned)pthread_self(), (char*)pthread_getspecific(key));
	
	pthread_join(t1, (void**)0);	
}

