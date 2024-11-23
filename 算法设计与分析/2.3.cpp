#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,a[105][105],i;
int f[105][105],ans;
int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)
    {
		for(int j=1;j<=i;j++) scanf("%d",&a[i][j]);
	}
	f[1][1]=a[1][1];
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		{
			f[i][j]=max(f[i][j],f[i-1][j]+a[i][j]);
			f[i][j+1]=max(f[i][j+1],f[i-1][j]+a[i][j]);
		}
	}
	for(int i=1;i<=n;i++) ans=max(ans,f[n][i]);//遍历最后一行找到最大值
	printf("%d\n",ans);
	return 0;
}
