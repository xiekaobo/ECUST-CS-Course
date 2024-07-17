#include<iostream>
#include<stdio.h>
#include<cmath>
using namespace std;
struct process
{
    char processName[50];         //进程名
    int arrivalTime;              //到达时间
    int completionTime;           //完成时间
    int requiredTime;             //需要运行的时间
    int turnovertime;             //程序周转时间
    float weightedTurnaroundTime; //带权周转时间
    int No;                       //进程编号
    bool visited;                 //当前节点是否被访问过
    struct process* next;         //下一个节点指针
    char state;                   //进程的状态
    double cpu_time;              //已用CPU时间
};
int main()
{
    process a[100];
    int n, i, j, k, time = 0, pian;//time为系统当前时间,pian为时间片大小
    float sum1 = 0, sum2 = 0;//sum1是周转时间平均，sum2是带权周转时间平均
    cin >> n;
    cin >> pian;
    for (i = 1; i <= n; i++)
    {
        cin >> a[i].processName;
        cin >> a[i].arrivalTime;
        cin >> a[i].requiredTime;
        a[i].No = i;
        a[i].visited = false;
    }
    //FCFS算法
    cout << "---------------FCFS----------------" << endl;
    for (i = 1; i <= n; i++)
    {
        if (a[i].arrivalTime >= time)
        {
            time = a[i].arrivalTime;
            time += a[i].requiredTime;
            a[i].completionTime = time;
            a[i].turnovertime = a[i].completionTime - a[i].arrivalTime;
            a[i].weightedTurnaroundTime = 1.0 * a[i].turnovertime / a[i].requiredTime;
            sum1 += a[i].turnovertime;
            sum2 += a[i].weightedTurnaroundTime;
        }
        else
        {
            time += a[i].requiredTime;
            a[i].completionTime = time;
            a[i].turnovertime = a[i].completionTime - a[i].arrivalTime;
            a[i].weightedTurnaroundTime = 1.0 * a[i].turnovertime / a[i].requiredTime;
            sum1 += a[i].turnovertime;
            sum2 += a[i].weightedTurnaroundTime;
        }
    }
    sum1 = sum1 * 1.0 / n;
    sum2 /= n;
    for (i = 1; i <= n; i++)
    {
        cout << "第" << i << "个进程" << endl;
        cout << "进程名称" << a[i].processName << "完成时间" << a[i].completionTime <<
         " 周转时间" << a[i].turnovertime << "带权周转时间 " << a[i].weightedTurnaroundTime;
        cout << endl;
    }
    cout << "平均周转时间:" << sum1 << "平均带权周转时间:" << sum2 << endl;
    cout << "-----------------------------------" << endl;
    //SPN算法
    cout << "----------------SPN----------------" << endl;
    time = 0;
    sum1 = 0, sum2 = 0;
    process temp;
    for (i = n; i > 1; i--)
    {
        for (j = 1; j < i; j++)
        {
            if (a[j].requiredTime > a[j + 1].requiredTime)
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    int solved = 0;
    while (solved < n)
    {
        for (i = 1; i <= n; i++)
        {
            if (a[i].arrivalTime <= time)
            {
                if (a[i].visited == false)
                {
                    time += a[i].requiredTime;
                    a[i].completionTime = time;
                    a[i].turnovertime = a[i].completionTime - a[i].arrivalTime;
                    a[i].weightedTurnaroundTime = 1.0 * a[i].turnovertime / a[i].requiredTime;
                    sum1 += a[i].turnovertime;
                    sum2 += a[i].weightedTurnaroundTime;
                    a[i].visited = true;
                    solved++;
                    break;
                }
            }
        }
    }
    for (i = n; i > 1; i--)
    {
        for (j = 1; j < i; j++)
        {
            if (a[j].No > a[j + 1].No)
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    sum1 = sum1 * 1.0 / n;
    sum2 /= n;
    for (i = 1; i <= n; i++)
    {
        cout << "第" << i << "个进程" << endl;
        cout << "进程名称" << a[i].processName << "完成时间" << a[i].completionTime <<
        " 周转时间" << a[i].turnovertime << "带权周转时间 " << a[i].weightedTurnaroundTime;
        cout << endl;
    }
    cout << "平均周转时间:" << sum1 << "平均带权周转时间:" << sum2 << endl;
    cout << "-----------------------------------" << endl;
    //RR算法
    cout << "----------------RR-----------------" << endl;
    time = 0, solved = 0;
    sum1 = 0, sum2 = 0;
    for (i = 1; i <= n; i++)
    {
        a[i].visited = false;
        a[i].state = 'W';
        a[i].cpu_time = 0;
    }
    process* headProcess = NULL, * tailProcess = NULL;//运行队列首尾指针
    int flag = n;//待运行进程个数
    while (flag) {//当n个进程未运行结束时
        while (headProcess == NULL) {//当运行队列为空时
            for (int i = 1; i <= n; i++) {//将当前时间已到达且未完成的进程按顺序进入运行队列
                if (a[i].arrivalTime <= time && a[i].state == 'W') {
                    a[i].state == 'R';
                    if (headProcess == NULL) {
                        headProcess = tailProcess = &a[i];
                        tailProcess->next = NULL;
                    }
                    else {
                        tailProcess->next = &a[i];
                        tailProcess = tailProcess->next;
                        tailProcess->next = NULL;
                    }
                }
            }
            if (headProcess == NULL) {//当前时间没有进程可运行
                time++;
            }
        }
        //有进程在运行队列中时
        //有进程在运行队列中时，运行队首进程
        if ((headProcess->requiredTime - headProcess->cpu_time) > pian) {//队首进程所需时间大于一个时间片
            time += pian;
            headProcess->cpu_time += pian;
        }
        else {//队首进程所需时间<=一个时间片
            time += headProcess->requiredTime - headProcess->cpu_time;
            headProcess->cpu_time += headProcess->requiredTime - headProcess->cpu_time;

        }

        //检查是否有新进程要进入运行队列
        for (int i = 1; i <= n; i++) {
            if (a[i].arrivalTime <= time && a[i].state == 'W') {
                a[i].state = 'R';
                tailProcess->next = &a[i];
                tailProcess = tailProcess->next;
                tailProcess->next = NULL;
            }
        }
        if (headProcess->cpu_time == headProcess->requiredTime) {//队首进程使用CPU时间已满需求
            headProcess->state = 'F';
            headProcess->completionTime = time;
            headProcess->turnovertime = headProcess->completionTime - headProcess->arrivalTime;//周转时间
            headProcess->weightedTurnaroundTime = 1.0*headProcess->turnovertime / headProcess->requiredTime;//带权周转时间
            sum1 += headProcess->turnovertime;
            sum2 += headProcess->weightedTurnaroundTime;
            flag--;
            headProcess = headProcess->next;
        }
        else {//队首进程放至队尾
            tailProcess->next = headProcess;
            tailProcess = tailProcess->next;
            headProcess = headProcess->next;
            tailProcess->next = NULL;
        }
    }
    sum1 = sum1 * 1.0 / n;
    sum2 /= n;
    for (i = 1; i <= n; i++)
    {
        cout << "第" << i << "个进程" << endl;
        cout << "进程名称" << a[i].processName << "完成时间" << a[i].completionTime << " 周转时间"
        << a[i].turnovertime << "带权周转时间 " << a[i].weightedTurnaroundTime;
        cout << endl;
    }
    cout << "平均周转时间:" << sum1 << "平均带权周转时间:" << sum2 << endl;
    return 0;
}
