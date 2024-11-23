#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

const int MAX = 50;
int board[MAX][6];  //存储n个立方体各面的颜色
int solu[MAX][6];   //存储解
int n;  //立方体个数、颜色种数
int ans = 0;  //解的个数
int used[MAX];
char color[MAX];

//找到一个解后，输出
void out(int edge[])
{
    int i, j, k, a, b, c, d;
    for(i=0; i<2; i++) //2个子图
    {
        for(j=0; j<n; j++)
            used[j] = 0;
        do{
            j = 0;
            d = c = -1;
            while(j<n && used[j]>0) //找下一条未用的边
                j++;
            if(j < n)
                do{
                    a = board[j][edge[i*n+j]*2];
                    b = board[j][edge[i*n+j]*2+1];
                    if(b == d)  //如果上一条边的终点与b相同，说明b为始点，交换，保证a为始点
                        swap(a, b);  //保证有向边的始点对应于前面和左面，终点对应于背面和右面
                    solu[j][i*2] = a;
                    solu[j][i*2+1] = b;
                    used[j] = 1;
                    if(c<0)  //开始顶点
                        c = a;
                    d = b;
                    for(k=0; k<n; k++)  //找下一个立方体
                        if(used[k]==0 && (board[k][edge[i*n+k]*2]==b || board[k][edge[i*n+k]*2+1]==b))
                            j = k;
                }while(b != c);  //找了一圈，回到起点
        }while(j<n);  //所有立方体都找遍
    }
    for(j=0; j<n; j++) //立方体的顶面和底面的颜色
    {
        k = 3 - edge[j] - edge[j+n];
        a = board[j][k*2];
        b = board[j][k*2+1];
        solu[j][4] = a;
        solu[j][5] = b;
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<6; j++)
            cout << color[solu[i][j]];
        cout << endl;
    }
}

void search()
{
    int i, t, cube;
    bool ok, newg, over;
    int *vert = new int[n];  //记录子图中每个顶点的度，应均为2
    int *edge = new int[n*2];  //记录每个立方体中边被选用的条数，每个立方体只有3条边，有两个子图要选用
    for(i=0; i<n; i++)
        vert[i] = 0;
    t = -1;
    newg = true;
    while(t > -2)
    {
        t++;
        cube = t % n;  //每个立方体找2次，得到真实的立方体编号，也是子图中边的编号
        if(newg)  //如果没有边被选入子图
            edge[t] = -1;
        over = false;  //是否结束，即两个子图构建完成
        ok = false;    //标记边是否已用过，两个子图不应有公共边
        while(!ok && !over)
        {
            edge[t]++;  //边被选用加入子图，使用次数增加
            if(edge[t]>2)  //在立方体每对相对面的顶点连一条边，每个立方体只有3条边
                over = true;
            else
                ok = (t<n || edge[t]!=edge[cube]);  //是否已用过
        }
        if(!over)
        {          //检测边的两个顶点的度
            if(++vert[board[cube][edge[t]*2]] > 2+t/2*2) //如果是第一个子图，顶点度不能超过2
                ok = false;              //如果是第二个子图，加上第一个子图，顶点度不能超过4
            if(++vert[board[cube][edge[t]*2+1]] > 2+t/2*2)
                ok = false;
            if(t%n == n-1 && ok)  //如果一个或两个子图已构建完成
                for(i=0; i<n; i++)
                    if(vert[i] > 2+t/n*2)
                        ok = false;
            if(ok)
            {
                if(t == n*2-1) //找到解
                {
                    ans++;
                    out(edge);
                    return;
                }
                else
                    newg = true;
            }
            else //取下一条边
            {
                --vert[board[cube][edge[t]*2]];  //边的两个顶点
                --vert[board[cube][edge[t]*2+1]];
                t--;
                newg = false;
            }
        }
        else //回溯
        {
            t--;
            if(t > -1)
            {
                cube = t % n;
                --vert[board[cube][edge[t]*2]];
                --vert[board[cube][edge[t]*2]];
            }
            t--;
            newg = false;
        }
    }
}

int main()
{

    cin >> n;
    for(int i=0; i<n; i++)
    {
        cin >> color[i];
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<6; j++)
        {
            cin >> board[i][j];
        }
    }
    search();
    if(ans == 0)
        cout << "No Solution！\n";
    cout << endl;
    return 0;
}
