#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

int a[25][3];
bool b[25];
int c[25];
int k;

void dfs(int m, int step)
{
    c[step] = m;
    if(step == 19 )
    {
        int ans = 0;

        for(int j = 0; j < 3; j++)
        {
            if(a[m][j] == c[0])
                ans = 1;
        }
        if(ans == 0)
            return ;
        printf("%d:  ", k);
        for(int i = 0; i <= step; i++)
        {
            printf("%d ", c[i]);
        }
        printf("%d\n", c[0]);
        k++;
        return;
    }




    for(int i = 0; i < 3; i++)
    {
        if(b[a[m][i]] == 0)
        {
            b[a[m][i]] = 1;
            dfs(a[m][i], step+1);
            b[a[m][i]] = 0;
        }
    }

}

int main()
{
    int i, j, m;
    for(i = 1; i <= 20; i++)
    {
        for(j = 0; j < 3; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    while(scanf("%d", &m)!=EOF){
        if(m == 0)
            break;
        k = 1;
        memset(b, 0, sizeof(b));

        b[m] = 1;
        dfs(m, 0);
    }

    return 0;
}

