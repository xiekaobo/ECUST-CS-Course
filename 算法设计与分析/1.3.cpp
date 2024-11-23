#include<bits/stdc++.h>
using namespace std;
int seq(int A,int B,int n)
{
    int ans;
    if(n==1||n==2) return 1;
    else ans=(A*seq(A,B,n-1)+B*seq(A,B,n-2))%7;
    return ans;
}
int main()
{
    int a,b,n,i,s=0;
    while(1)
    {
        cin>>a>>b>>n;
        if(a==0&&b==0&&n==0) break;
        else
        {
            s=seq(a,b,n);
            printf("%d\n",s);
        }
    }
    return 0;
}
