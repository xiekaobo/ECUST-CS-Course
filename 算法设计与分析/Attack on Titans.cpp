#include<bits/stdc++.h>
#define MAXN 1000010
#define INF 1000000000
#define MOD 1000000007
#define LL long long
using namespace std;
LL dp[MAXN][4];
int main() {
    int n, m, k;
    while (cin>>n>>m>>k)
        {
        dp[0][1] = 1;
        dp[0][2] = dp[0][3] = 0;
        for (int i = 1; i <= n; ++i)
        {
            dp[i][1]=dp[i][2]=dp[i][3]=0;
            dp[i][1]=dp[i-1][1]+dp[i-1][2]+dp[i-1][3];
            dp[i][1]%=MOD;
            dp[i][2]=dp[i-1][1]+dp[i-1][2]+dp[i-1][3];
            dp[i][2]%=MOD;
            dp[i][3]=dp[i-1][1]+dp[i-1][2]+dp[i-1][3];
            dp[i][3]%=MOD;
            if (i==k+1)
            {
                dp[i][3]=(dp[i][3]-1+MOD)%MOD;
            }
            else if(i>k + 1)
            {
                dp[i][3]=(dp[i][3]-dp[i-k-1][1]-dp[i-k-1][2]+2LL*MOD) % MOD;
            }
        }
        LL ans=dp[n][1]+dp[n][2]+dp[n][3];
        ans%=MOD;
        for (int i=1;i<=n;++i)
            {
            dp[i][1] = dp[i][2] = dp[i][3] = 0;
            dp[i][1] = dp[i-1][1]+dp[i-1][2]+dp[i-1][3];
            dp[i][1] %= MOD;
            dp[i][2] = dp[i-1][1]+dp[i-1][2]+dp[i-1][3];
            dp[i][2] %= MOD;
            dp[i][3] = dp[i-1][1]+dp[i-1][2]+dp[i-1][3];
            dp[i][3] %= MOD;
            if(i==k+1)
            {
                dp[i][3] = (dp[i][3]-1 + MOD) % MOD;
            }
            else if (i > k + 1)
            {
                dp[i][3]=(dp[i][3]-dp[i-k-1][1]-dp[i-k-1][2]+2LL*MOD)%MOD;
            }
            if(i==m)
            {
                dp[i][1]=(dp[i][1]-1+MOD)%MOD;
            } else if (i > m)
            {
                dp[i][1]=(dp[i][1]-dp[i-m][2]-dp[i-m][3]+2LL*MOD)%MOD;
            }
        }
        ans=(ans-dp[n][1]-dp[n][2]-dp[n][3]+3LL*MOD) % MOD;
        cout<<ans<<endl;
    }
    return 0;
}


