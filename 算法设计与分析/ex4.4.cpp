#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=1e4+9;
int n,m,a[maxn];
double b[maxn],dp[maxn];  //dp[i]：预算为i，得到一份offer的最大概率
int main()
{
	while(cin>>n>>m)     //预算为n元 m个学校
	{
		if(n+m==0)
			break;
		memset(dp,0,sizeof(dp));
		for(int i=1; i<=m; i++)
			cin>>a[i]>>b[i];  //申请第i个学校的费用 和通过的概率
		for(int i=1; i<=m; i++)
		{
			for(int j=n; j>=a[i]; j--) //类似01背包
			{
				dp[j]=max(dp[j],1-(1-dp[j-a[i]])*(1-b[i]));
			}
		}
		printf("%.1f%%\n",dp[n]*100);
	}
	return 0;
}
