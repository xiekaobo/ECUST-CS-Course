#include <cstring>
#include <cstdio>
#define maxn 20
#define lowbit(x) (x & (-x))
#define maxs (1 << maxn)
#define INF 0x7f
int line[maxn][maxn], ans[maxn], anscnt = 0, dp[maxs], cnt[maxs], n, rs, pre[maxs], qpow[maxn];
int main(void)
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			scanf("%d", &line[i][j]), line[j][i] = line[i][j];
	memset(dp, INF, sizeof(dp));
	rs = 1 << n;
	qpow[0] = 1;
	for (int i = 1; i < n; ++i)
		qpow[i] = qpow[i - 1] << 1;
	for (int i = 1, temp = 0, old = 0; i < rs; ++i, temp = lowbit(i), old = i - temp)
	{
		int pos = 0;
		cnt[i] = cnt[old];
		while (temp >>= 1)
			++pos;
		for (int j = 0; j < n; ++j, old >>= 1)
			if (old & 1)
				cnt[i] -= line[pos][j];
			else cnt[i] += line[pos][j];
	}
	dp[0] = 0;
	for (int i = 1, temp = i; i < rs; ++i, temp = i)
		for (int j = 0; temp; ++j, temp >>= 1)
			if ((temp & 1))
				if (dp[i] > dp[i - qpow[j]] + cnt[i - qpow[j]])
				{
					dp[i] = dp[i - qpow[j]] + cnt[i - qpow[j]];
					pre[i] = j;
				}
	printf("%d\n", dp[--rs]);
	while (rs)
	{
		ans[anscnt++] = pre[rs];
		rs -= qpow[pre[rs]];
	}
	for (int i = 0; i < anscnt; ++i)
		printf("%d ", ans[i] + 1);
	return 0;
}
