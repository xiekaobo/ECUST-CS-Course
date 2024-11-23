#include<iostream>
#include<string>
using namespace std;
int main()
{
	int n, i,red=0,yellow=0;
	char a[20];
	while (1)
	{
		cin >> n;
		if (n == 0) break;
		else
		{
			red = 0, yellow = 0;
			for (i = 1; i <= n; i++)
			{
				cin >> a[i];
				if (a[i] == 'R') red++;
				if (a[i] == 'Y') yellow++;	
			}
			if (a[n] == 'B')
			{
				if (red == 7)
				{
					cout << "Red" << endl;
				}
				if (red != 7)
				{
					cout << "Yellow" << endl;
				}
			}
			if (a[n] == 'L')
			{
				if (yellow == 7)
				{
					cout << "Yellow" << endl;
					break;
				}
				if (yellow != 7)
				{
					cout << "Red" << endl;
					break;
				}
			}
		}
	}
	return 0;
}