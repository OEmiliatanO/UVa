#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <unistd.h>

using namespace std;

constexpr int MAXN = 200;

int64_t G[MAXN + 5][MAXN + 5];
int lev[MAXN + 5];
bool vis[MAXN + 5];
int s, t;

void bfs()
{
	memset(lev, 0, sizeof(int) * (MAXN + 5));
	queue<int> qu;

	qu.push(s);
	lev[s] = 1;
	while(qu.size())
	{
		int u = qu.front(); qu.pop();
		
		//cout << "now: " << u << endl;
		//cout << "lev[now]: " << lev[u] << endl;
		for (int v = 1; v <= t; ++v)
		{
			if (v == s) continue;
			//cout << "v: " << v << endl;
			//cout << "lev[v]: " << lev[v] << endl;

			if (lev[v] || G[u][v] <= 0) continue;
			
			lev[v] = lev[u] + 1;
			if (v == t) return;
			qu.push(v);
		}
		//sleep(1);
	}

	/*
	cout << "in bfs" << endl;
	for (int i = 1; i <= t; ++i)
		cout << lev[i] << ' ';
	cout << endl;
	sleep(1);
	*/
}

int64_t dfs(int u, int64_t lim)
{
	if (u == t)
		return lim;
	
	/*
	cout << "now: " << u << '\n';
	cout << "lim: " << lim << '\n';
	*/
	
	for (int v = 1; v <= t; ++v)
	{
		if (v == s) continue;
		/*
		cout << "\tnow: " << u << '\n';
		cout << "\tnex: " << v << '\n';
		cout << "\tG[u][v]: " << G[u][v] << '\n';
		cout << "\tlim: " << lim << '\n';
		*/

		//cout << "\tf: " << f << '\n';

		//sleep(1);
		if (vis[v] || G[u][v] <= 0 || lev[v] != lev[u] + 1) continue;
		
		int64_t f = dfs(v, min(G[u][v], lim));
		vis[v] = true;
		if (f != 0)
		{
			G[u][v] -= f;
			G[v][u] += f;
			return f;
		}
	}

	return 0;
}

int main()
{
	int n, m;
	while(~scanf("%d", &n))
	{
		s = 2 * n + 1, t = 2 * n + 2;
		memset(G, 0, sizeof(int64_t) * (MAXN + 5) * (MAXN + 5));
		
		for (int i = 1; i <= n; ++i)
		{
			int x, u = i, v = n + i;
			scanf("%d", &x);
		
			G[u][v] = x; G[v][u] = x;
		}

		scanf("%d", &m);
		for (int i = 1; i <= m; ++i)
		{
			int u, v, x;
			scanf("%d %d %d", &u, &v, &x);
			u += n;
			G[u][v] += x;
		}

		int b, d;
		scanf("%d %d", &b, &d);
		for (int i = 1; i <= b; ++i)
		{
			int v;
			scanf("%d", &v);
			G[s][v] = (int64_t)1e10; // s to v
		}
		for (int i = 1; i <= d; ++i)
		{
			int u;
			scanf("%d", &u);
			u += n;
			G[u][t] = (int64_t)1e10; // u to t
		}
		
		int64_t flow = 0;
		while(1)
		{
			bfs();
			if (!lev[t])
				break;
			int64_t tmp;
			while(1)
			{
				memset(vis, 0, sizeof(bool) * (MAXN + 5));
				if ((tmp = dfs(s, 1e10))) flow += tmp;
				else break;

				//cout << "flow: " << flow << '\n';
				//cout << "tmp: " <<  tmp << '\n';
				//sleep(1);
			}
		}

		printf("%lld\n", (long long)flow);
	}

	return 0;
}
