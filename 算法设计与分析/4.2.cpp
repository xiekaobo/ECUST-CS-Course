#include<iostream>
#include<cstring>
using namespace std;

#define MAX_NODE 999

int max_cut=0;
int n,m;
int cut_pos[MAX_NODE];
void cal_max_cut(int n,int m,bool is_connected[][MAX_NODE],int cut[],int i)
{
    if(i==n+1)
    {
        int count=0;
        for(int i=1;i<=n;i++)
        {
            for(int j=i+1;j<=n;j++)
            {
                if(is_connected[i][j] && cut[i]!=cut[j])
                    count++;
            }
        }
        if(count>max_cut)
        {
            max_cut=count;
            for(int i=1;i<=n;i++)
            {
                if(cut[i] == 2)
                {
                    cut_pos[i]=0;
                    continue;
                }
                cut_pos[i]=cut[i];
            }
        }
        return;
    }
    cut[i]=1;
    cal_max_cut(n,m,is_connected,cut,i+1);
    cut[i]=2;
    cal_max_cut(n,m,is_connected,cut,i+1);
}

int main()
{
    cin>>n>>m;
    bool is_connected[MAX_NODE][MAX_NODE];
    memset(is_connected,false,sizeof(is_connected));
    for(int i=0;i<m;i++)
    {
        int x,y;
        cin>>x>>y;
        is_connected[x][y]=true;
        is_connected[y][x]=true;
    }
    int cut[n+1];
    memset(cut,0,sizeof(cut));
    cal_max_cut(n,m,is_connected,cut,1);
    cout<<max_cut<<endl;
    for(int i=1;i<=n;i++)
        cout<<cut_pos[i]<<" ";
    return 0;
}
