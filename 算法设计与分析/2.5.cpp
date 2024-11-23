#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int kk,len,big;
int num[100010][4];
string s1,s2;
const int MAX=100000;
bool FL;
int ctoi(char x)
{
	return (int)x-'0';
}
int N(string s){
    int ret=0;
    for(int i=0;i<s.length();i++) ret=ret*10+s[i]-'0';
    return ret;
}
void input(){
    cin>>s1>>s2;
    len=s1.length();
    big=81*len+9;
    if(big<171) big=171;
    kk=N(s2);
    if(big<kk)
    {
		printf("-1\n");
		FL=true;
	}
}

void count(int i,int j)
{
    if(i<num[j][1]) num[j][1]=i;
    if(i>num[j][2]) num[j][2]=i;
    num[j][3]+=i;
}

void init(){
    for(int i=0;i<=big;i++)
    {
        num[i][0]=MAX;
        num[i][1]=MAX;
        num[i][2]=0;
        num[i][3]=0;
    }
    for(int i=0;i<len;i++) count(ctoi(s1[i]),0);
    num[0][0]=0;
    for(int i=1;i<=big;i++)
    {
        int t=i;
        while(t>0)
        {
            int j=t%10;
            t/=10;
            count(j,i);
        }
    }
}
void compute()
{
    bool flag=true;
    while(flag){
        flag=false;
        for(int i=0;i<=big;i++){
        	if(num[i][0]<MAX)
            {
        		for(int k=0;k<=big;k++)
                {
       				if(num[k][0]<MAX)
       				{
            			int j=num[i][3]*num[k][2]+num[k][1];
            			if(num[i][0]+num[k][0]+1<num[j][0])
            			{
                			num[j][0]=num[i][0]+num[k][0]+1;
                			flag=true;
                		}
                	}
                }
            }
        }
    }
    if(num[kk][0]<MAX) printf("%d\n",num[kk][0]);
    else printf("-1\n");
}

int main()
{
	while(true)
        {
		FL=false;
		input();
		if(FL) continue;
    	if(s1==s2)
        {
    		if(s1.length()==1&&s1[0]=='0') return 0;
			printf("0\n");
			continue;
		}
    	init();
    	compute();
	}
    return 0;
}
