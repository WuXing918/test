#include <stdio.h>
#include <string.h>
int next(char* mod,char i,int j)
{
	printf("mod = %s,j = %c\n",mod,j);
	int len = strlen(mod);
	char* str = mod+len-1;
	printf("str= %s\n",str);
	while(i != *str)
	{	
		str--;
		if(len--)
		{
			return j+1; 
		}
		printf("mod = %s ,len = %d\n",str,len);
		
	}
	return j-len+1;
}
int Boyer_Moore(char* str,char* mod)
{
	int l_str = strlen(str);
	int l_mod = strlen(mod);
	int i = l_mod-1;
	while(i<l_str)
	{	int l = i;
		int j = l_mod-1;
		while(j>=0){
			if(str[i]==mod[j])
			{
				i--;
				j--;
			}else{
				i = l + next(mod,str[i],i);	
				break;
			}
		}
		if(j<0)
		{
			return i+1;
		}	
	}
	return -1;
}

int main()
{
	char buf[]="abcdefgwuxing hijklmnowuxuxpqrstuvwxyz wuxingnihao";
	char mod[]="wuxing";
	int r= Boyer_Moore(buf,mod);
	if(r==-1)
	{
		perror("error");
	}else{
		printf("%s\n",buf+r);
	}
}
/*
	该算法从后向前进行匹配，采用，坏字符，好后缀两大规则进行移位匹配。
	几个关键的地方：
		坏字符的位置:
			是在mod中对应的位置；
		坏字符上一次出现的位置：
			在mod中没有出现的话位置为-1，否则为他的位置，从右边匹配。
	
*/

