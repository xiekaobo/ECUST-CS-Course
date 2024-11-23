#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,i,floor=0,f;
    int ans;
    while(1)
    {
        cin>>n;
        if(n==0) break;
        else
        {
            floor=0;
            ans=0;
            for(i=1;i<=n;i++)
            {
                cin>>f;
                if(f>floor)
                {
                    ans+=(f-floor)*6+5;
                    floor=f;
                }
                else if(f<floor)
                {
                    ans+=(floor-f)*4+5;
                    floor=f;
                }
                else ans+=5;
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
