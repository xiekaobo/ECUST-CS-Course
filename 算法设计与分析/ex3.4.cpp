#include <bits/stdc++.h>
using namespace std;

int n;
int boy[21][21], girl[21][21];
int Max = INT_MIN; //MAX代表男女双方竞赛优势的总和的最大值 用来返回指定整数类型所能表示的最小值。
int sum = 0;
int res[21][21]; //data[i][j]用于存放男运动员i配对后的双方竞赛优势
int maxSum[21];   //保存每个男生匹配后可达到的最大双方竞赛优势
int book[21];    //标记女运动员是否已经匹配 0未匹配 1已匹配

//Max：40 -> 52
void dfs(int t){
    if(t>=n)  //t到达n后，代表全部标记访问了，得到了最大值
    {
        Max = max(Max, sum);
        return;
    }
    int cnt = 0;
    //求t及t之后男生匹配女生的最大值的和
    for (int i = t; i < n;i++){
        cnt += maxSum[i];
        //假设的贪心的让每个男运动员匹配最优的女运动员
    }

    //剪枝函数：之前t个已经匹配好的男女运动员的sum与
    //之后的t->n-1个男女匹配的最大值加起来得到的Max比较
    //若前者<=Max，剪枝
    if(sum+cnt<Max)
        return;
        //若cnt>=Max，要继续向下搜索
        //从第t个男生开始匹配，找未匹配的女生
    for (int i = 0; i < n;i++){
        if(!book[i]){//若第i个女生未匹配
            book[i] = 1;
            sum += res[t][i];
            dfs(t + 1);
            book[i] = 0; //若第t个男生匹配女生i得到的sum不大于Max，则回溯
            sum -= res[t][i];
        }
    }
}

int main(){
    cin >> n;
    for (int i = 0; i < n;i++){
        for (int j = 0; j < n;j++){
            cin >> boy[i][j];
        }
    }
    for (int i = 0; i < n;i++){
        for (int j = 0; j < n;j++){
            cin >> girl[i][j];
        }
    }
    for (int i = 0; i < n;i++){
        for (int j = 0; j < n;j++){
            //对每个男生都求男女双方竞赛优势，能得到i*j种结果
            res[i][j] = boy[i][j] * girl[j][i];
            //记录每个男生匹配后可达到的最大双方竞赛优势，用于后面的剪枝
            maxSum[i] = max(maxSum[i], res[i][j]);
        }
    }
    dfs(0);
    cout << Max << endl;
    return 0;
}
