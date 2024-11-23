//这是按照助教的思路写的代码 
#include<iostream>
#include<queue>
using namespace std;
typedef struct Treenode{
    int data;
    struct Treenode *lchild, *rightbro;
}*Tree;
void printq(queue<int> q)
{
    while(!q.empty())
    {
        cout<<q.front()<<"-";
        q.pop();
    }
    cout<<endl;
}
std::queue<int> q;
void Search(Tree T)
{
    if(T[0].lchild!=NULL)
    {
        q.push(T[0].data);
        Search(T[0].lchild);
    }
    else if(T[0].lchild==NULL)
    {
        printq(q);
        q.pop();
        Search(T[0].rightbro);

    }
}
Tree Getroot(int data[],int degree[],int length)
{
    Tree p=new Treenode[length];
    for(int i=0;i<length;i++)
    {
        p[i].data=data[i];
        p[i].lchild=p[i].rightbro=NULL;
    }
    int d,nodeid=0;
    for(int i=0;i<length;i++)
    {
        d=degree[i];
        if(d)
        {
            nodeid++;
            p[i].lchild=&p[nodeid];
            for(int j=2;j<=d;j++)
            {
                nodeid++;
                p[nodeid-1].rightbro=&p[nodeid];
            }
        }
    }
    return p;
}
int main()
{
    int a[1000],b[1000],len,i;
    scanf("%d",&len);
    for(i=1;i<=len;i++)
    {
        scanf("%d%d",&a[i],&b[i]);
    }
    Tree t=Getroot(a,b,len);
    Search(t);
    return 0;
}
