#include<cstdio>
#include<iostream>
using namespace std;
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
int main()
{
    int a,b,c;
    while(scanf("%d%d%d",&a,&b,&c),a+b+c)
    {
        a/=gcd(b,c);
        if(a&1)printf("NO\n");
        else printf("%d\n",a-1);
    }
    return 0;
}
