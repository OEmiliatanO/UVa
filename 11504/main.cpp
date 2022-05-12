#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

constexpr int MAXN = 1e5;

int t, scc[MAXN + 1], in[MAXN + 1];
vector<int> G[MAXN + 1], rG[MAXN + 1], order;
bool vis[MAXN + 1];

void rDfs(int now)
{
	vis[now] = true;
	for (auto nex : rG[now])
		if (!vis[nex]) rDfs(nex);
	order.emplace_back(now);
}

void dfs(int now, int s)
{
	scc[now] = s;
	for (auto nex : G[now])
		if (scc[nex] == -1)
			dfs(nex, s);
		else
			++in[scc[nex]];
}

int findscc(int n)
{
	for (int i = 1; i <= n; ++i)
		if (!vis[i])
			rDfs(i);

	int NScc = 1;
	for (int i = n; i >= 1; --i)
	{
		int now = order[i - 1];
		if (scc[now] == -1)
			dfs(now, NScc++);
	}

	return NScc - 1;
}

int main()
{
	scanf("%d", &t);
	while(t--)
	{
		int n, m;
		scanf("%d %d", &n, &m);

		order.clear();
		for (int i = 0; i <= n; ++i)
		{
			G[i].clear();
			rG[i].clear();
			vis[i] = false;
			scc[i] = -1;
			in[i] = 0;
		}

		for (int i = 0; i < m; ++i)
		{
			int x, y;
			scanf("%d %d", &x, &y);
			G[x].emplace_back(y);
			rG[y].emplace_back(x);
		}

		int NScc = findscc(n);
		int ans = 0;
		for (int i = 1; i <= NScc; ++i)
			(!in[i]) && (++ans);

		printf("%d\n", ans);
	}
	return 0;
}
