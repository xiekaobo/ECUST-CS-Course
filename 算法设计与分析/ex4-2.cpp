#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
int a,b,c,t;
int map[51][51][51],dis[6][3]={{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
bool biao[51][51][51];
struct ch
{
    int x,y,z,step;
};
bool panduan(int x,int y,int z)
{
    if(x<0||y<0||z<0||x>=a||y>=b||z>=c)return 0;
    if(biao[x][y][z]||map[x][y][z])return 0;
    return 1;
}
int bfs(int x,int y,int z)
{
    queue<ch>ha;
    ch sta,next;
    int i,j;
    sta.x=x;
    sta.y=y;
    sta.z=z;
    sta.step=0;
    biao[x][y][z]=1;
    ha.push(sta);

    while(!ha.empty())
    {
        sta=ha.front();
        ha.pop();
        if(sta.x==a-1&&sta.y==b-1&&sta.z==c-1)
        {
            return sta.step;
        }

        if(sta.step>t)
        {
            return -1;
        }

        for(i=0;i<6;i++)
        {
            next.x=sta.x+dis[i][0];
            next.y=sta.y+dis[i][1];
            next.z=sta.z+dis[i][2];
            if(panduan(next.x,next.y,next.z))
            {
                next.step=sta.step+1;
                biao[next.x][next.y][next.z]=1;
                ha.push(next);
            }
        }
    }
    return -1;
}
int main()
{
    int i,j,z,n;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d%d%d%d",&a,&b,&c,&t);
        for(i=0;i<a;i++)
        {
            for(j=0;j<b;j++)
            {
                for(z=0;z<c;z++)
                {
                    scanf("%d",&map[i][j][z]);
                }
            }
        }
        memset(biao,false,sizeof(biao));
        printf("%d\n",bfs(0,0,0));
    }
    return 0;
}
