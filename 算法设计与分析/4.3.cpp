#include <bits/stdc++.h>
using namespace std;

int n;    //部件数量
int m;    //供应商数量
int d;    //价格上限
int bestw;   //最小的重量
int** c = NULL;    //二维数组，每个部件不同商家的价格
int** w = NULL;     //二维数组，每个部件不同商家的重量
//每一个部件的信息
class Node {
public:
    int weight;        //当前已选机器的重量和
    int val;           //当前已选机器的价值和
    int source;        //哪个供货商
    int level;         //第几层,也代表了第几个部件
    int priority;      //优先级
    Node* father;
};

Node* leaf;//叶子结点
void Input() {
    scanf("%d %d %d",&n,&m,&d);
    w = (int**)malloc(sizeof(int*)*(n + 1));
    c = (int**)malloc(sizeof(int*)*(n + 1));
    for (int i = 1; i <= n; i++) {
        w[i] = (int*)malloc(sizeof(int)*(m + 1));
        c[i] = (int*)malloc(sizeof(int)*(m + 1));
    }
    leaf = NULL;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d",&c[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d",&w[i][j]);
}

//优化的优先级设定
bool operator<(Node a, Node b)  //level按照减序
{
    if (a.priority == b.priority)return a.level < b.level;  //如果重量相同，选择level大的。
    return a.priority > b.priority;//否则，重量小的先出队
}

//计算当前节点的优先级
void QueuePriority(Node a) {
    int currentMinW;
    a.priority = a.val;
    //int temp_min_c = INT_MAX;
    for (int i = a.level + 1; i <= n; i++)//选出剩余的部件在售货商中购买的最小质量,就是选择每一层最小的质量
    {
        currentMinW = 999999;
        for (int j = 1; j <= m; j++)  //每一层找最小的
        {
            currentMinW = currentMinW < w[i][j] ? currentMinW : w[i][j];//从m个商家中选择当层重量最小的
        }
        a.priority += currentMinW;
    }
}

//约束函数
bool constraint(Node* pNode, int i) {
    return pNode->val + c[pNode->level + 1][i] <= d || pNode->weight + w[pNode->level + 1][i] <= bestw;
}

//创建节点
Node createNode(int level, Node* father, int source, int val, int weight) {
    Node newNode{};
    newNode.level = level;//层次加1
    newNode.father = father;
    newNode.source = source;
    newNode.val = val;
    newNode.weight = weight;
    return newNode;
}

void MinWeightMachine() {
    int i, j;
    bestw = 999999;
    Node initial{};
    initial = createNode(0, NULL, 0, 0, 0);
    QueuePriority(initial);      //计算优先级
    priority_queue<Node> heap;   //用优先队列，建立一个最小堆。加入进去就会自动排好序的。
    heap.push(initial);
    while (!heap.empty()) {
        Node* pNode = new Node(heap.top());
        heap.pop();//队首元素作为父节点出队，即优先级值小的活结点先扩展
        if (pNode->level == n)//到达叶节点，不能扩展 ,得到一个解
        {
            if (pNode->weight < bestw)   //更新
            {
                bestw = pNode->weight;
                //MinValue  = pNode ->val;
                leaf = pNode;   //记录是最后是哪个结点数据,便于回溯找最优解
            }
        }
        else {
            for (i = 1; i <= m; i++)//扩展结点，依次选择每个售货商，每次都是m叉树
            {
                //可行性剪枝和限界剪枝
                if (constraint(pNode, i)) {
                    Node newNode{};//生儿子结点
                    newNode = createNode(pNode->level + 1, pNode, i, pNode->val + c[pNode->level + 1][i], pNode->weight + w[pNode->level + 1][i]);
                    QueuePriority(newNode);     //计算优先值
                    heap.push(newNode);//儿子入队
                }
            }
        }
    }

}

void Output() {
    printf("%d\n",bestw);
    int* result = (int*)malloc(sizeof(int)*(n + 1));
    for (int i = n; i >= 1; i--) {
        result[i] = leaf->source;//从最后叶子结点回溯到根节点
        leaf = leaf->father;
    }
    for (int i = 1; i <= n; i++)
        if(i==1) printf("%d",result[i]);
        else printf(" %d",result[i]);
    putchar('\n');
}
int main() {
    Input();
    MinWeightMachine();
    Output();
    return 0;
}
