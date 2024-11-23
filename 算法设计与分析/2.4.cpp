#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int dp[1000],r[1000][1000],n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
    {
		for(int j=i+1;j<=n;j++) scanf("%d",&r[i][j]);
	}
	memset(dp,0x3f,sizeof(dp));
	dp[1]=0;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<i;j++) dp[i]=min(dp[i],dp[j]+r[j][i]);
	}
	printf("%d\n",dp[n]);
	return 0;
}
