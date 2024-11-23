#include<bits/stdc++.h>
using namespace std;
class Solution
{
    int partition( vector<int>& nums, int l, int r)
    {
    int pivot = nums[r];
    int i = l - 1;
    for (int j = l; j <= r - 1; ++j)
    {
    if (nums[j] <= pivot)
    {
    i = i + 1;
    swap ( nums[i], nums[j]);
    }
    }
    swap( nums[i + 1], nums[r]);
    return i + 1;
}
//基于随机的划分
int randomized_partition(vector<int>& nums,int l, int r)
{
int i = rand( ) % (r - l + 1) + l;
swap(nums[r], nums[i]);
return partition(nums, l, r);
}
void randomized_selected(vector<int>& stock,int l, int r, int cnt)
{
    if ( l >= r) {return;}
    int pos = randomized_partition(stock, l, r);
    int num = pos - l + 1;
    if (cnt == num) {return;}
    else if (cnt < num) {randomized_selected(stock,l, pos - 1, cnt);}
    else {randomized_selected( stock, pos + 1, r, cnt - num);}
}
public:
vector<int> inventoryManagement(vector<int>& stock, int cnt)
{
    srand ( (unsigned )time (NULL) );
    randomized_selected(stock,0,(int)stock.size( ) - 1, cnt);
    vector<int> vec;
    for (int i = 0; i < cnt; ++i){vec.push_back( stock[i]);}
    return vec;
}
};
int main()
{
    int n; // 数组长度
    cin >> n;
    vector<int> stock(n); // 创建长度为 n 的数组
    for (int i = 0; i < n; ++i)
    {
        cin >> stock[i]; // 逐个输入数组元素
    }
    int cnt; // 输入 cnt
    cin >> cnt;
    Solution obj; // 创建 Solution 类的对象
    vector<int> result = obj.inventoryManagement(stock, cnt); // 调用 inventoryManagement 函数
    // 打印结果
    for (int i = 0; i < result.size(); ++i)
    {
        cout << result[i] << " ";
    }
    cout<<endl;
    return 0;
}
