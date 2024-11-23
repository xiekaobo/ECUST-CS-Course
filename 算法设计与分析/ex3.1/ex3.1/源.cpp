#include<iostream>
using namespace std;
const int N = 1000;
int a[N]; // 存储集合元素
bool vis[N]; // 存储集合元素的状态
int subSum;  //子集当前和
int flag = 0;//标记是否找到过解
int n, c;

void print(int i) {//输出符合条件的子集的元素
	for (int j = 0; j <= i; j++) {
		if (vis[j] == true) {
			if (j != i)printf("%d ", a[j]);
			else printf("%d\n", a[j]);
		}
	}
}
void search(int i) {
	//小于，就继续往后加数；大于，就回溯返回上一节点；等于，就输出，再回溯返回上一节点
	if (i >= n) 	return;	//超出范围
	vis[i] = true;
	subSum += a[i];
	if (subSum == c) {//满足 输出
		flag = 1;//表示我找到过符合条件的子集
		print(i);
	}
	else if (subSum < c) {// 不足 继续取数
		search(i + 1);
	}
	//如果subSum > m,就回溯,把当前加入的数拿掉，进入上一个节点继续找
	vis[i] = false;
	subSum -= a[i];
	search(i + 1);//从下一个数开始
	return;
}

int main() {
	cin >> n >> c;
	for (int i = 0; i < n; i++)	cin >> a[i];
	search(0);
	if (!flag)	printf("No Solution!");
	return 0;
}

