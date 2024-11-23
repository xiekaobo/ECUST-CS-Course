#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,a[205],b[205],sum,i;
int dp[205][205*100],ans;

int main()
{
    FILE *input_file;
    FILE *output_file;
    input_file = fopen("input.txt", "r");
	fscanf(input_file,"%d",&n);
	for(i=1;i<=n;i++)
    {
        fscanf(input_file,"%d",&a[i]);
    }
    for(i=1;i<=n;i++)
    {
        fscanf(input_file,"%d",&b[i]);
    }
    fclose(input_file);
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=sum=0;
	for(int i=1;i<=n;i++)//dp[i][j]表示前i个a处理机用时小于等于j时b处理机的用时
	{
		for(int j=0;j<=sum;j++)
        {
			dp[i][j+a[i]]=min(dp[i][j+a[i]],dp[i-1][j]);//表示第i个任务由a处理机处理的情况
			dp[i][j]=min(dp[i][j],dp[i-1][j]+b[i]);//表示第i个任务由b处理机处理的情况
		}
		sum+=a[i];
	}
	ans=2e9;
	for(int i=0;i<=sum;i++) ans=min(ans,max(i,dp[n][i]));
	output_file = fopen("output.txt", "w");
    fprintf(output_file,"%d",ans);
    fclose(output_file);
	return 0;
}
