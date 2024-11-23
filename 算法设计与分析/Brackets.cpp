#include<bits/stdc++.h>
using namespace std;
string a;
int i,left1=0,left2=0,ans=0;
int main()
{
    while(1)
    {
    ans=0,left1=0,left2=0;
    cin>>a;
    if(a=="end") break;
    for(i=0;i<a.length();i++)
    {
        if(a[i]=='(') left1++;
        if(a[i]==')')
        {
            if(left1>0)
            {
                left1--;
                ans+=2;
            }
        }
        if(a[i]=='[') left2++;
        if(a[i]==']')
        {
            if(left2>0)
            {
                left2--;
                ans+=2;
            }
        }
    }
    cout<<ans<<endl;
    }
    return 0;
}
