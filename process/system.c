#include <stdlib.h>
#include <unistd.h>
int main()
{
	/*system函数创建一个子进程，创建子进程的同时就开始执行子进程，
	父进程等待子进程结束后再进行执行。
	*/
	int flag = system("ls -l");
	sleep(10);
	flag = system("./a.out");

}
/* system的源码 
int system(const char * cmdstring)
{
    pid_t pid;
    int status;

    if(cmdstring == NULL){
          
         return (1);
    }


    if((pid = fork())<0){

            status = -1;
    }
    else if(pid == 0){
        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        -exit(127); //子进程正常执行则不会执行此语句
        }
    else{
            while(waitpid(pid, &status, 0) < 0){
                if(errno != EINTER){
                    status = -1;
                    break;
                }
            }
        }
        return status;
}
*/
