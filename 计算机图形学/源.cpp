#include <stdio.h>

#define MAX 10000

// 进程结构体
struct Process {
    int pid;            // 进程ID
    double arrival_time;   // 到达时间
    double finish_time;    // 完成时间
    double process_time;   // 运行时间
    double cpu_time;       // 已用 CPU 时间
    double turnover_time;  // 周转时间
    double turnover_weight_time;// 带权周转时间
    char state;         // 进程状态，就绪 W（Wait）、运行 R（Run）和完成 F（Finish ） 三种状态之一
    struct Process *next;
};

void FCFS(Process processes[],int n) {
    int time = 0;//当前时间
    double average_turnover_time = 0,average_turnover_weight_time = 0;
    for (int i = 0; i < n; i++) {
        if (time < processes[i].arrival_time)time = processes[i].arrival_time;//开始运行时间
        processes[i].finish_time = time + processes[i].process_time;//完成时间
        processes[i].cpu_time = processes[i].process_time;// 已用 CPU 时间
        processes[i].turnover_time = processes[i].finish_time - processes[i].arrival_time;//周转时间
        processes[i].turnover_weight_time = processes[i].turnover_time / processes[i].process_time;//带权周转时间
        processes[i].state = 'F';
        time += processes[i].process_time;
        average_turnover_time += processes[i].turnover_time;
        average_turnover_weight_time += processes[i].turnover_weight_time;
    }
    average_turnover_time /= n;
    average_turnover_weight_time /= n;
    printf("FCFS 平均周转时间:%lf 平均带权周转时间:%lf\n", average_turnover_time, average_turnover_weight_time);
}

void SPN(Process processes[],int n) {
    int time = 0;
    double average_turnover_time = 0, average_turnover_weight_time = 0;
    for (int i = 0; i < n; i++) {//运行n个进程
        int process_pid = i, min_process_time = MAX;
        for (int j = 0; j < n; j++) {//找到当前时间下最短进程
            if (processes[j].arrival_time <= time && processes[j].process_time < min_process_time && processes[j].state == 'W') {
                process_pid = processes[j].pid;
                min_process_time = processes[j].process_time;
            }
        }
        if (min_process_time == MAX) time = processes[i].arrival_time;//若当前时间为找到可运行进程，加快时间至下一个可运行进程
        processes[process_pid].finish_time = time + processes[process_pid].process_time;//完成时间
        processes[process_pid].cpu_time = processes[process_pid].process_time;// 已用 CPU 时间
        processes[process_pid].turnover_time = processes[process_pid].finish_time - processes[process_pid].arrival_time;//周转时间
        processes[process_pid].turnover_weight_time = processes[process_pid].turnover_time / processes[process_pid].process_time;//带权周转时间
        processes[process_pid].state = 'F';
        time += processes[process_pid].process_time;
        average_turnover_time += processes[process_pid].turnover_time;
        average_turnover_weight_time += processes[process_pid].turnover_weight_time;
    }
    average_turnover_time /= n;
    average_turnover_weight_time /= n;
    printf("SPN 平均周转时间:%lf 平均带权周转时间:%lf\n", average_turnover_time, average_turnover_weight_time);
}

void RR(Process processes[],int n) {
    int time = 0;
    double average_turnover_time = 0, average_turnover_weight_time = 0;
    Process *headProcess=NULL, *tailProcess = NULL;//运行队列首尾指针

    int flag = n;//待运行进程个数
    while (flag) {//当n个进程未运行结束时
        while (headProcess == NULL) {//当运行队列为空时
            for (int i = 0; i < n; i++) {//将当前时间已到达且未完成的进程按顺序进入运行队列
                if (processes[i].arrival_time <= time && processes[i].state == 'W'){
                    if (headProcess == NULL) {
                        headProcess = tailProcess = &processes[i];
                        tailProcess->next = NULL;
                    }else {
                        tailProcess->next = &processes[i];
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
        headProcess->cpu_time++;
        time++;
        for (int i = 0; i < n; i++) {//检查是否有新进程要进入运行队列
            if (processes[i].arrival_time == time) {
                tailProcess->next = &processes[i];
                tailProcess = tailProcess->next;
                tailProcess->next = NULL;
            }
        }
        if (headProcess->cpu_time == headProcess->process_time) {//队首进程使用CPU时间已满需求
            headProcess->state = 'F';
            headProcess->finish_time = time;
            headProcess->turnover_time = headProcess->finish_time - headProcess->arrival_time;//周转时间
            headProcess->turnover_weight_time = headProcess->turnover_time / headProcess->process_time;//带权周转时间
            average_turnover_time += headProcess->turnover_time;
            average_turnover_weight_time += headProcess->turnover_weight_time;
            flag--;
            headProcess = headProcess->next;
        }else {//队首进程放至队尾
            tailProcess->next = headProcess;
            tailProcess = tailProcess->next;
            headProcess = headProcess->next;
            tailProcess->next = NULL;
        }
    }
    average_turnover_time /= n;
    average_turnover_weight_time /= n;
    printf("RR 平均周转时间:%lf 平均带权周转时间:%lf\n", average_turnover_time, average_turnover_weight_time);
}

void restoreProcess(Process processes[], int n) {//恢复进程数组数据
    for (int i = 0; i < n; i++) {
        processes[i].finish_time = MAX;
        processes[i].cpu_time = 0;
        processes[i].state = 'W';
    }
}

int main() {
    Process processes[] = {
        {0,0,MAX,2,0,MAX,MAX,'W',NULL},
        {1,1,MAX,5,0,MAX,MAX,'W',NULL},
        {2,2,MAX,4,0,MAX,MAX,'W',NULL},
        {3,3,MAX,2,0,MAX,MAX,'W',NULL},
        {4,4,MAX,3,0,MAX,MAX,'W',NULL},
    };
    int n= sizeof(processes) / sizeof(processes[0]);
    
    FCFS(processes, n);
    restoreProcess(processes, n);
    SPN(processes, n);
    restoreProcess(processes, n);
    RR(processes, n);

    return 0;
}