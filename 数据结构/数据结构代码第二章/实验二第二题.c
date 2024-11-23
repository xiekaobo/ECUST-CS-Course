#include<stdio.h>
#include<stdlib.h>
typedef struct AVLNode * AVLTree;//注意AVLTree的类型是结构体指针，指向对象是结构体
struct AVLNode{
    int Data;
    AVLTree Left;
    AVLTree Right;
    int Height;
};
int max(int a,int b)
{
    return a>b?a:b;
}
int GETHeight(AVLTree T)//p117
{
    int hl,hr,maxh;
    if(T)
    {
        hl=GETHeight(T->Left);
        hr=GETHeight(T->Right);
        maxh=hl>hr?hl:hr;
        return (maxh+1);
    }
    else return 0;
}
AVLTree Singleleft(AVLTree A)//p141
{
    AVLTree B=A->Left;
    A->Left=B->Right;
    B->Right=A;
    A->Height=max(GETHeight(A->Left),GETHeight(A->Right))+1;
    B->Height=max(GETHeight(B->Left),A->Height)+1;
    return B;
}
AVLTree Singleright(AVLTree A)
{
    AVLTree B=A->Right;
    A->Right=B->Left;
    B->Left=A;
    A->Height=max(GETHeight(A->Left),GETHeight(A->Right))+1;
    B->Height=max(GETHeight(B->Right),A->Height)+1;
    return B;
}
AVLTree Doubleleftright(AVLTree A)
{
    A->Left=Singleright(A->Left);
    return Singleleft(A);
}
AVLTree Doublerightleft(AVLTree A)
{
    A->Right=Singleleft(A->Right);
    return Singleright(A);
}
AVLTree INSERT(AVLTree T, int X)//p139
{
    if(!T)
    {
        T=(AVLTree)malloc(sizeof(struct AVLNode));
        T->Data=X;
        T->Height=1;
        T->Left=T->Right=NULL;
    }
    else if(X<T->Data)
    {
        T->Left=INSERT(T->Left,X);
        if(GETHeight(T->Left)-GETHeight(T->Right)==2)
        {
            if(X<T->Left->Data) T=Singleleft(T);
            else T=Doubleleftright(T);
        }
    }
    else if(X>T->Data)
    {
        T->Right=INSERT(T->Right,X);
        if(GETHeight(T->Left)-GETHeight(T->Right)==-2)
        {
            if(X>T->Right->Data) T=Singleright(T);
            else T=Doublerightleft(T);
        }
    }
    T->Height=max(GETHeight(T->Left),GETHeight(T->Right))+1;
    return T;
}
void preorder(AVLTree T)//p112
{
    if(T)
    {
        printf("%d ",T->Data);
        preorder(T->Left);
        preorder(T->Right);
    }
    else printf("# ");
}
int main()
{
    AVLTree T1=NULL;//注意T1的数据类型是结构体指针，采用了动态存储方式，所以必须初始化！
    int N,i,node;
    scanf("%d",&N);
    for(i=1;i<=N;i++)
    {
        scanf("%d",&node);
        T1=INSERT(T1,node);
    }
    preorder(T1);
    return 0;
}
