#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<deque>
#include<iostream>
int ceng[99999999];
typedef struct TNode *BinTree;
struct TNode{
    char Data;
    BinTree Left;
    BinTree Right;
}T1;
//求二叉树的宽度
int WidthOfBiTree(BinTree root)
{
    if(root == NULL)
        return 0;
    int maxWidth = 0;
    std::deque<BinTree> d;//利用双端队列实现层序遍历
    d.push_back(root);
    while(true)
    {
        int len = d.size();
        if(len == 0)
            break;
        while(len > 0)
        {
            BinTree temp = d.front();
            d.pop_front();
            len--;
            if(temp->Left)
                d.push_back(temp->Left);
            if(temp->Right)
                d.push_back(temp->Right);
        }
        maxWidth = maxWidth > d.size() ? maxWidth : d.size();

    }
    return maxWidth;
}
BinTree CreateBinTree()
{
    char ch;
    BinTree T=NULL,left=NULL,right=NULL;
    ch=getchar();
    if(ch=='#') return NULL;
    else
    {
        T=(BinTree)malloc(sizeof(struct TNode));
        T->Data=ch;
        left=CreateBinTree();
        if(left!=NULL)    T->Left=left;
        else T->Left=NULL;
        right=CreateBinTree();
        if(right!=NULL) T->Right=right;
        else T->Right=NULL;
    }
    return T;
}
int main()
{
    int ans;
    BinTree T1;
    T1=CreateBinTree();
    ans=WidthOfBiTree(T1);
    printf("%d",ans);
    return 0;
}
