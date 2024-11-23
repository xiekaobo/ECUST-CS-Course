#include<bits/stdc++.h>
using namespace std;
struct Status//定义结构体，维护4个变量
{int lSum,rSum,mSum,iSum;};
struct Status pushUp(struct Status l, struct Status r)
{
int iSum = l.iSum + r.iSum; //左右子区间的区间和为整体区间和
int lSum = fmax ( l.lSum,l.iSum + r.lSum) ;
int rSum = fmax(r.rSum, r.iSum + l.rSum) ;
int mSum = fmax ( fmax( l.mSum,r.mSum), l.rSum + r.lSum ) ;
return (struct Status){lSum,rSum,mSum,iSum} ;
};
 struct Status get(int* a, int l, int r)
{
if ( l == r) {return (struct Status ){a[l],a[l], a[l], a[l]};}//当区间长度为1时
int m = ( l +r) >> 1;//将区间分为左右两个子区间分治求解
struct Status lSub = get(a, l, m); //左子区间的4个变量值
struct Status rSub = get(a, m + 1,r); //右子区间的4个变量值
return pushUp( lSub, rSub);//“合并"左右子区间的值
}
int maxSubArray (int* nums, int numssize) {return get(nums, 0,numssize - 1).mSum;}
int main()
{
    int a[10000]={0};
    int n,i;
    int ans=0;
    cin>>n;
    for(i=0;i<n;i++){cin>>a[i];}
    ans=maxSubArray(a,n);
    printf("%d",ans);
    return 0;
}
