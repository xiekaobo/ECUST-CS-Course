#include<stdio.h>
#include<stdlib.h>
#define INFINITY 1000000000
typedef struct LNode *PtrtoNode;
struct LNode
{
    int xishu,zhishu;
    PtrtoNode Next;
};
typedef PtrtoNode List;
int main()
{
    int a,b;
    PtrtoNode L=(List)malloc(sizeof(struct LNode));//头结点申请空间
    PtrtoNode Head=L;
    L->Next=NULL;
    L->xishu=INFINITY;
    L->zhishu=INFINITY;
    scanf("%d%d",&a, &b);
    if(a==0&&b==0) { printf("0"); return 0;}
    A:while(a!=0||b!=0)
    {
        List i=Head;
        while(i!=NULL)
        {
            if(i->zhishu==b) //判断是否可以合并同类项
                {
                i->xishu=i->xishu+a;
                scanf("%d%d",&a,&b);
                goto A;
                }
            else i=i->Next;
        }
        PtrtoNode p=(List)malloc(sizeof(struct LNode));
        p->xishu=a;
        p->zhishu=b;
        p->Next = NULL;
        L->Next=p;
        L=L->Next;
        scanf("%d%d",&a,&b);
    }

    char p;
    p=getchar();

    scanf("%d%d",&a,&b);
    if(a==0&&b==0) {List i=Head->Next; goto B;}
    A1:while(a!=0||b!=0)
    {
        List i=Head;
        while(i!=NULL)
        {
            if(i->zhishu==b) //判断是否可以合并同类项
                {
                i->xishu=i->xishu+a;
                scanf("%d%d",&a,&b);
                goto A1;
                }
            else i=i->Next;
        }
        PtrtoNode p=(List)malloc(sizeof(struct LNode));
        p->xishu=a;
        p->zhishu=b;
        p->Next=NULL;
        L->Next=p;
        L=L->Next;
        scanf("%d%d",&a,&b);
    }

    List i = Head->Next;
    B:if(i->xishu==1)
    {
        if(i->zhishu==1) printf("x");
        else if (i->zhishu==0) printf("1");
        else printf("x^%d",i->zhishu);
    }
    else if (i->xishu==0)
    {
        i=i->Next;
        goto B;
    }
    else if (i->zhishu==1) printf("%dx",i->xishu);
    else if (i->zhishu==0) printf("%d",i->xishu);
    else printf("%d^x%d",i->xishu,i->zhishu);
    i=i->Next;
    for(;i!=NULL;i=i->Next)
    {
        if(i->xishu==1)
        {
        if(i->zhishu==1) {printf("+x"); continue;}
        else if (i->zhishu==0) {printf("+1"); continue;}
        }
        else if (i->xishu==0) continue;
        if (i->zhishu==1) printf("+%dx",i->xishu);
        else if (i->zhishu==0) printf("+%d",i->xishu);
        else printf("+%d^x%d",i->xishu,i->zhishu);
    }
    return 0;
}
