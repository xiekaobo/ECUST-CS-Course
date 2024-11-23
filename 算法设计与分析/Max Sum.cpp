#include<iostream>
#include<cstdio>
#define N 100010
using namespace std;
int a[N],d[N];

int main(){
    int test,n,i,max,k=1,f,e;
    scanf("%d",&test);
    while(test--){
        scanf("%d",&n);
        for(i=1;i<=n;i++) scanf("%d",&a[i]);
        d[1]=a[1];
        for(i=2;i<=n;i++)
        {
            if(d[i-1]<0) d[i]=a[i];
            else d[i]=d[i-1]+a[i];
        }
        max=d[1];e=1;
        for(i=2;i<=n;i++)
        {
            if(max<d[i])
            {
                max=d[i];e=i;
            }
        }
        int t=0;
        f=e;
        for(i=e;i>0;i--){
            t=t+a[i];
            if(t==max) f=i;
        }
        printf("Case %d:\n%d %d %d\n",k++,max,f,e);
        printf("\n");
    }
    return 0;
}
