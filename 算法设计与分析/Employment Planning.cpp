#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,x,y,z,m;
int a[15];
int dp[15][20005],ans;
int main(){
	while(scanf("%d",&n)!=EOF)
    {
		if(n==0) break;
		scanf("%d %d %d",&x,&y,&z);
		m=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			m=max(m,a[i]);
		}
		memset(dp,0x3f,sizeof(dp));
		for(int i=a[1];i<=m;i++) dp[1][i]=x*i+y*i;
		for(int i=2;i<=n;i++)
		{
			for(int j=a[i];j<=m;j++)
			{
				for(int k=0;k<=m;k++)
				{
					if(k<=j) dp[i][j]=min(dp[i][j],dp[i-1][k]+x*(j-k)+y*j);
					else dp[i][j]=min(dp[i][j],dp[i-1][k]+z*(k-j)+y*j);
				}
			}
		}
		ans=1e9;
		for(int i=a[n];i<=m;i++) ans=min(ans,dp[n][i]);
		printf("%d\n",ans);
	}
	return 0;
}
