#include<bits/stdc++.h>
using namespace std;
void dfs( char* str, int s, int e, char *res, int *max)
{
if(s >= e) return;
bool f = true;
int i;
for(i=s ;i<=e ;i++)
{
//查找str[i]对应的大写(小写)字符是否存在，若存在还要判断字符是否落在s ~ e区间内
    char *pos = strchr(str+s,str[i] <= 'Z' ? str[i]+32 : str[i]-32);
    if(!(pos && pos <= str+e ))
    {
        f = false;
        break;
    }
}
if(!f)
{
//如果str[i〕在str[s~e]内为非法字符，则递归处理左部和右部，先处理左部因为题目要求返回先出现的结果
dfs (str, s, i-1, res,max );
dfs(str, i+1,e, res,max ) ;
}
else
{
    //l如果str[s~e]是一个完美字符串,判断其长度是否符合题意，若符合则替换
    if(e-s+1 > *max )
    {
        *max = e-s+1;
        for(int i=s ;i<=e;i++) {res[i-s] = str[i];}
    }
}
}
int main()
{
    string c;
    string ans="";
    cin >> c;
    char* p = (char*)c.c_str(); // 获取输入字符串的 C 风格字符串
    char* p0 = (char*)ans.c_str();
    int max_length = 0;
    dfs(p, 0, c.length(), p0, &max_length);
    // 输出结果字符串
    for (int i = 0;p0[i] != '\0'; i++) {
        printf("%c", p0[i]);
    }
    return 0;
}
