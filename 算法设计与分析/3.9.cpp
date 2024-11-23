#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,ans=0,temp=0,i;
    int fac[10]={1,1,2,6,24,120,720,5040,40320,362880};
    for(i=1;i<=3628800;i++)
    {
        ans=0;
        temp=i;
        while(temp!=0)
        {
            ans+=fac[temp%10];
            temp/=10;
        }
        if(ans==i) cout<<i<<endl;
    }
    return 0;
}
