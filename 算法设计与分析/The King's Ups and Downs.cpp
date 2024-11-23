#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
int n;
int a,b;
ll dp[22][2],C[22][22],sum[22];

int main(){
	C[0][0]=1;
	for(int i=1;i<=20;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	dp[0][0]=dp[0][1]=1;
	dp[1][0]=dp[1][1]=1;
	sum[1]=1;
	for(int i=2;i<=20;i++){
		ll t=0;
		for(int j=0;j<i;j++) t+=C[i-1][j]*dp[j][0]*dp[i-1-j][1];
		dp[i][0]=dp[i][1]=t/2;
		sum[i]=t;
	}
	scanf("%d",&n);
	while(n--){
		scanf("%d %d",&a,&b);
		printf("%d %lld\n",a,sum[b]);
	}

	return 0;
}
