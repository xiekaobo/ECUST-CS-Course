#include<bits/stdc++.h>
using namespace std;
int count_in_range(int* nums,int target,int lo,int hi)// 计算指定范围内数组中某个特定元素target的出现次数
{
    int count=0;
    for(int i=lo;i<=hi;++i)
    {
        if (nums[i]==target) ++count;
    }
    return count;
}
int majority_element_rec(int* nums,int lo, int hi)
{
    if (lo==hi) return nums[lo];// 区间长度为1时，众数即为该数本身
    int mid = (lo + hi) / 2;// 中间索引mid
    int left_majority=majority_element_rec(nums,lo,mid);// 左半部分的众数
    int right_majority=majority_element_rec(nums,mid+1,hi); //右半部分的众数
    if (count_in_range(nums,left_majority,lo,hi)>(hi-lo+1)/2) return left_majority;
    if (count_in_range(nums,right_majority,lo,hi)>(hi-lo+1)/2) return right_majority;
    return -1; // 左半部分和右半部分都没有多数元素，则返回-1
}
int majorityElement(int* nums, int numsSize)
{
    return majority_element_rec(nums,0,numsSize-1);
}
int main()
{
    int a[10000]={0};
    int n,i,ans=0;
    cin>>n;
    for(i=0;i<n;i++){cin>>a[i];}
    ans=majorityElement(a,n);
    printf("%d",ans);
    return 0;
}
