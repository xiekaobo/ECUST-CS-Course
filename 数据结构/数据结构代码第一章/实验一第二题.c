#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 1000
char a[MAXSIZE];
char b[MAXSIZE];
typedef struct SNode *PtrtoNode;
typedef PtrtoNode Stack;
struct SNode{
    char *Data;
    int top;
    int maxsize;
};
int main()
{
    int N;
    scanf("%d",&N);
    char temp;
    int i,j,count,flag=1;
    Stack S1=(Stack)malloc(sizeof(struct SNode));
    S1->Data=(char*)malloc(N*sizeof(char));
    S1->top=-1;
    S1->maxsize=N;
    for(i=0;i<2*N;i++)
    {
        scanf("%c",&a[i]);//入栈序列输入
    }
    for(i=0;i<2*N;i++)
    {
        scanf("%c",&b[i]);//出栈序列输入
    }
    j=1;//出栈序列栈尾指针
    for(count=1,i=1;count<=N;count++,i+=2)//遍历入栈序列
    {
        if(a[i]!=b[j]&&i<=2*N-1)
        {
            S1->Data[++(S1->top)]=a[i];//压栈
            //printf("%c-in\n",a[i]);
        }
        else if(a[i]==b[j]&&i<=2*N-1)
        {
            S1->Data[++(S1->top)]=a[i];
            //printf("%c-in\n",a[i]);
            while(S1->Data[S1->top]==b[j])
            {
                //printf("%c-out\n",S1->Data[S1->top]);
                S1->Data[S1->top]==' ';//出栈清空
                if(S1->top!=-1) (S1->top)--;//栈顶指针回溯
                j+=2;//出栈序列指针后移，准备判断下一阶段是否可以出栈
            }
        }
    }
    if(j==2*N+1) printf("1\n");
    else {printf("0"); return 0;}
    //和上述代码块一样 只不过增加输出语句
    j=1;
    S1->top=-1;//栈顶指针归位，准备遍历
    for(count=1,i=1;count<=N;count++,i+=2)
    {
        if(a[i]!=b[j]&&i<=2*N-1)
        {
            S1->Data[++(S1->top)]=a[i];
            printf("%c-in\n",a[i]);
        }
        else if(a[i]==b[j]&&i<=2*N-1)
        {
            S1->Data[++(S1->top)]=a[i];
            printf("%c-in\n",a[i]);
            while(S1->Data[S1->top]==b[j])
            {
                printf("%c-out\n",S1->Data[S1->top]);
                S1->Data[S1->top]==' ';
                if(S1->top!=-1) (S1->top)--;
                j+=2;
            }
        }
    }
    return 0;
}
