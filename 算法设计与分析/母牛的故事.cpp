#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,i;
unsigned long long f[60];
int main(){
	for(i=1;i<=4;i++) f[i]=i;
	for(int i=5;i<=55;i++) f[i]=f[i-1]+f[i-3];
	while(scanf("%d",&n))
    {
		if(n==0) break;
		printf("%d\n",f[n]);
	}
	return 0;
}
