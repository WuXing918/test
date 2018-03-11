#include <unistd.h>
#include <stdio.h>
/*
	exec函数族主要与vfork()函数配合使用.主要是在一进程中启动新的可执行程序.
当进程调用一种exec函数时，该进程执行的程序完全替换为新程序，而新程序则从其main()函数开始执行.
    Attention!!!
    1、调用exec函数族并不创建一新的进程，所以前后进程ID并不改变.exec只是用一个全新的程序替换了当前进程的正文、数据、堆和栈.
    2、exec函数族提供了在一进程中启动另一程序执行的方法.另一程序可以是二进制文件，也可以是linux下任何可执行的脚本文件.

*/
int main()
{
	printf("_______________________--\n");
	printf("将要用exec族函数来执行心得程序\n");
	printf("_______________________--\n");
	exec("./system",NULL);
}