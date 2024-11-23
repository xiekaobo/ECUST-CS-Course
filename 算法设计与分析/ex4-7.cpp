#include<stdio.h>
#include<queue>
#include<string.h>
#include<algorithm>
using namespace std;
int book[2][15][15];
char  a[2][15][15];
struct node
{
    int x,y,z,step;
};
int main()
{
    int i,j,k,f,n,m,t,T;
    int ta,tb,tc,tx,ty,tz;
    int next [4][2]= {0,1,1,0,0,-1,-1,0};
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&t);
        getchar();
        for(i=0; i<2; i++)
        {
            for(j=0; j<n; j++)
            {
                for(k=0; k<m; k++)
                    scanf("%c",&a[i][j][k]);
                getchar();
            }
            if(i!=1) getchar();//这个吸收中间那个空白行，注意只有一个空白行。
        }
        for(i=0; i<2; i++)
            for(j=0; j<n; j++)
            {
                for(k=0; k<m; k++)
                    if(a[i][j][k]=='P')//记录公主的位置，顺便把'P'改为'.',(纯属个人习惯)。
                    {
                        ta=i;
                        tb=j;
                        tc=k;
                        a[i][j][k]='.';
                    }
                    else  if(a[i][j][k]=='#'&&a[i^1][j][k]=='#')//如果这一层是#，另一层还是#，直接标记为墙就行。
                    {
                        a[0][j][k]='*';
                        a[1][j][k]='*';
                    }
                    else  if(a[i][j][k]=='#'&&a[i^1][j][k]=='*')//这一层是#，另一层是墙，这样会撞死（骑士也不傻）。
                    {
                        a[0][j][k]='*';
                        a[1][j][k]='*';
                    }
            }
        memset(book,0,sizeof(book));
        book[0][0][0]=1;
        queue<node>Q;
        node p,q;
        f=0;
        p.x=0,p.y=0,p.z=0,p.step=0;
        Q.push(p);
        while(!Q.empty())
        {
            p=Q.front();
            Q.pop();
            if(p.x==ta&&p.y==tb&&p.z==tc&&p.step<=t&&f==0)
            {
                f=1;
                // printf("%d\n",p.step);
                printf("YES\n");
                break;
            }
            for(i=0; i<4; i++)
            {
                tx=p.x;
                ty=p.y+next[i][0];
                tz=p.z+next[i][1];
                if(a[tx][ty][tz]=='*'||book[tx][ty][tz]==1||tx<0||tx>1||ty<0||ty>n-1||tz<0||tz>m-1)
                    continue;
                if(a[tx][ty][tz]=='.')
                {
                    book[tx][ty][tz]=1;
                    q.x=tx,q.y=ty,q.z=tz;
                    q.step=p.step+1;
                    Q.push(q);
                }
                else if(a[tx][ty][tz]=='#')
                {
                    book[tx][ty][tz]=1;
                    if(tx==0)//传送门可以换层（(⊙o⊙)哦，传送门是什么东东，怎么听着这么熟悉）。
                        tx+=1;
                    else tx-=1;

                    if(a[tx][ty][tz]=='*'||book[tx][ty][tz]==1||tx<0||tx>1||ty<0||ty>n-1||tz<0||tz>m-1)
                        continue;
                    book[tx][ty][tz]=1;
                    q.x=tx,q.y=ty,q.z=tz;
                    q.step=p.step+1;
                    Q.push(q);
                }
            }
        }
        while(!Q.empty())
            Q.pop();
        if(!f)  printf("NO\n");
    }
    return 0;
}
