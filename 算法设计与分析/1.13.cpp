#include<bits/stdc++.h>
using namespace std;
int main()
{
    double ans=0,m;
    for(int i=1;i<=12;i++)
    {
        cin>>m;
        ans+=m/12;
    }
    cout<<"$"<<ans<<endl;
    return 0;
}
