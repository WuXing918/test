#include <stdio.h>
#include <time.h>

int main(){
	//time_t is a struct 
	time_t t;
	time(&t);
	struct tm *time = localtime(&t);
	printf("%d\n",time->tm_year+1900);
	printf("%d\n",time->tm_mon);
	printf("%d\n",time->tm_mday);
	

}


