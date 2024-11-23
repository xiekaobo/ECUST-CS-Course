#include <bits/stdc++.h>
using namespace std;

int n,m;
int depth=1;   //子集树的深度。一层一层的找，最后若形成子集树，说明变换成功，此深度就是最少变换次数
string str="";   //回溯的记录结果

bool dfs(int n,int curDepth)
{
    if(curDepth>depth)   //当前搜索层超过子集树的深度，返回
        return false;
    int operation=n;   //进行两步操作：左子树：n*3；右子树：n/2;
    for(int i=0;i<2;i++)
    {
        i==0?operation=3*n:operation=n/2;   //如果i=0，进入左子树；否则，进入右子树
        if(operation==m||dfs(operation,curDepth+1))   //如果经过上述操作后，得到的数operation = m，或者经过下一次操作后，得到的数operation = m
        {
            i==0?str+="f":str+="g";   //左子树操作：加“f”；右子树操作：加“g”
            return true;   //满足条件就可以返回了
        }
    }
    return false;
}
int main()
{
    cin>>n>>m;
    while(!dfs(n,1))   //从第一层开始搜索。当dfs返回false,表示没有变换成功；否则，继续下一层循环，直到子集树建成
    {
        depth++;   //深度就是最小的变换次数
    }
    cout<<depth<<endl;
    cout<<str<<endl;
    return 0;
}
