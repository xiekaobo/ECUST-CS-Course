#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a[1000];
    int T,n,i;
    cin>>T;
    while(T--)
    {
        cin>>n;
        for(i=0;i<n;i++) {cin>>a[i];}
        sort(a,a+n);
        for(i=0;i<n;i++) {cout<<a[i]<<" ";}
        cout<<endl;
    }
    return 0;
}
