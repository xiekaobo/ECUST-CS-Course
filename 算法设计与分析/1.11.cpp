#include<bits/stdc++.h>
using namespace std;
int fac(int n)
{
    if(n==0||n==1) return 1;
    else return n*fac(n-1);
}
int main()
{
    double ans=0,m=0;
    cout<<"n e"<<endl;
    cout<<"- -----------"<<endl;
    for(int i=0;i<=9;i++)
    {
        m+=1.0/fac(i);
        if(i<=2) cout<<i<<" "<<m<<endl;
        else cout<<i<<" "<<fixed<<setprecision(9)<<m<<endl;
    }
    return 0;
}
