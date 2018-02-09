#include <stdio.h>
#include <string.h>
#include <signal.h>


int isstop=1;//定义bool值
void handle(int s)
{
	if(s==SIGUSR1)
	{
		if(isstop==1)
			isstop=0;
		else
			isstop=1;
	}
}
int match(char* Str,char* Mod,int l)
{
	int Slen = strlen(Str);
	int Mlen = strlen(Mod);
	int i=l;
	while(i<Slen){
		int nl = i;
		int j=0;
		while(j<Mlen)
		{
			if(Mod[j]==Str[i])
			{
				j++;
				i++;
			}else{
				i++;
				break;
			}	
		}
		if(j>=Mlen)
		{
			return nl;
		}
	}
	return -1;
}
void check(char* Str,char*Mod,int l)
{
	int r = match(Str,Mod,l);
	if(r==-1)
	{
		printf("file is end!\n");
		return;
	}else
	{
		printf("%s\n",Str+r);
			pause();
		check(Str+r,Mod,r);
	}
}
int main()
{
	if(fork()==0)
	{
		int ch;
		while(1)
		{
			ch = scanf("%d",&ch);
			if(ch== 1)
			{
				kill(getppid(),SIGUSR1);
			}
		}
		
	}else{
		signal(SIGUSR1,handle);
		char *str = "abcdewuxingfghijklmnwuxingopqrstuvwxyzwuxing";
		char *mod = "wuxing";
		check(str,mod,0);
	}
}












