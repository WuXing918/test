#include "Tool.h"
#include "math.h"
int showMenu()
{
	printf("-------------------\n");
	printf("欢迎进入图形库！\n");
	printf("-------------------\n");
	printf("请选择你需要的图形！\n");
	printf("[1]:矩形\n");
	printf("[2]:三角形\n");
	printf("[3]:菱形\n");
	printf("[0]:推出\n");
	printf("-------------------\n");
	printf("请输入：");
	int num;
	scanf("%d",&num);
	printf("%d\n",num);
	return num;
}
void onshow(){
	while(1)
	{
		switch(showMenu())
		{
			case 1:paintJ();break;
			case 2:paintS();break;
			case 3:paintL();break;
			case 0:printf("[0]:推出\n");exit(0);
		}	
	}

}
