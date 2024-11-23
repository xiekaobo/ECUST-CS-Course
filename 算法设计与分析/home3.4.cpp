#include <iostream>

using namespace std;

int a[3][3], count;
bool vis[10];

bool isprime(int n)
{
	for(int i = 2; i * i <= n; i++){
		if(n % i == 0) return false;
	}
	return true;
}

bool check(int x, int y, int k)
{
	// ÉÏ
	if(x - 1 >= 0 && !isprime(a[x - 1][y] + k)) return false;
	// ×ó
	if(y - 1 >= 0 && !isprime(a[x][y - 1] + k)) return false;
	return true;
}

void dfs(int x, int y)
{
	if(x == 3){
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				cout << a[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		count ++;
		return;
	}
	for(int i = 1; i <= 10; i++){
		if(!vis[i] && check(x, y, i)){
			a[x][y] = i; vis[i] = true;
			if(y == 2) dfs(x + 1, 0);
			else dfs(x, y + 1);
			a[x][y] = 0; vis[i] = false;
		}
	}
}

int main()
{
	dfs(0, 0);
	cout << "Total: " << count << endl;
	return 0;
}
