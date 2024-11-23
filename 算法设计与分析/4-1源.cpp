#include<iostream>

using namespace std;

#define MAX 50
int n, m;
int W[MAX] = { 0 };
int select[MAX] = { 0 };
int bestS[MAX] = {0}, minSum = 10000;

struct E {
	int left;
	int right;
} E[MAX] = {0};

bool isCover(int nowSelect[]) {
	bool flag=true;
	for (int i = 1; i <= m; i++) {
		if (nowSelect[E[i].left] == 0 && nowSelect[E[i].right] == 0) {
			flag = false;
			break;
		}
	}
	return flag;
}

void find_min_cover(int nowSelect[],int position,int sum) {
	if (position == n + 1) {
		if (isCover(nowSelect)) {
			minSum = sum;
			copy(nowSelect, nowSelect + n + 1, bestS);
		}
	}
	else {
		if (sum + W[position] < minSum) {//当前顶点选中
			nowSelect[position] = 1;
			find_min_cover(nowSelect, position + 1, sum + W[position]);
			nowSelect[position] = 0;
		}
		//当前顶点未选中
		find_min_cover(nowSelect, position + 1, sum);
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> W[i];
	}
	int v1, v2;
	for (int i = 1; i <= m; i++) {
		cin >> v1 >> v2;
		E[i].left = v1;
		E[i].right = v2;
	}
	find_min_cover(select, 1, 0);
	cout << minSum << endl;
	for (int i = 1; i <= n; i++) {
		cout << bestS[i] << " ";
	}
	return 0;
}