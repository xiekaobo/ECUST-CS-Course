#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int MIN[1000][1000];
int MAX[1000][1000];
int n,a[1000],sum[1000],r;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum[i]=sum[i-1]+a[i];
	memset(MIN,0x3f,sizeof(MIN));
	for(int i=1;i<=n;i++) MIN[i][i]=MAX[i][i]=0;
	for(int i=2;i<=n;i++)
    {
		for(int l=1;l<=n-i+1;l++)
		{
			r=l+i-1;
			for(int p=l;p<r;p++)
			{
				MIN[l][r]=min(MIN[l][r],MIN[l][p]+MIN[p+1][r]+sum[r]-sum[l-1]);//sum[r]-sum[l-1]Çø¼äºÍ
				MAX[l][r]=max(MAX[l][r],MAX[l][p]+MAX[p+1][r]+sum[r]-sum[l-1]);
			}
		}
	}
	printf("%d\n",MIN[1][n]);
	printf("%d\n",MAX[1][n]);

	return 0;
}
