#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
#include <utility>

using namespace std;

typedef pair<int, int> pii;

constexpr int MAXN = 100;

int cnts[MAXN + 5][MAXN + 5];
int ways[MAXN + 5][MAXN + 5];
pii from[MAXN + 5][MAXN + 5];
bool vis[MAXN + 5][MAXN + 5];
bool g[MAXN + 5][MAXN + 5];

int main()
{
	int n, m, kase = 1;
	while(~scanf("%d %d", &n, &m) && !(n == -1 && m == -1))
	{
		memset(cnts, 0, sizeof(cnts));
		memset(g, 0, sizeof(g));
		memset(ways, 0, sizeof(ways));
		memset(vis, 0, sizeof(vis));
		queue<pii> qu;
		
		int fix = -2, x, y;
		while(scanf("%d %d", &x, &y) && !(x == 0 && y == 0))
		{
			cnts[x][y] = 1;
			g[x][y] = true;

			if (x == 1 && y == 1)
				++fix;
			if (x == n && y == m)
				++fix;
		}
		
		if (fix > 0) fix = 0;
		qu.emplace(pii{1, 1});
		ways[1][1] = cnts[1][1] = cnts[n][m] = 1;
		vis[1][1] = true;
		while(qu.size())
		{
			pii now = qu.front(); qu.pop();
			//printf("%d %d\n", now.first, now.second);
			int upperm = m;
			for (int i = now.first; i <= n; ++i)
				for (int j = now.second; j < upperm; ++j)
				{
					if (i == now.first && j == now.second) continue;
					if (cnts[i][j])
					{
						//printf("%d %d\n", i, j);
						upperm = min(upperm, j);
						if (cnts[i][j] < cnts[now.first][now.second] + 1)
						{
							from[i][j] = pii{now.first, now.second};
							cnts[i][j] = cnts[now.first][now.second] + 1;
							ways[i][j] = ways[now.first][now.second];
						}
						else if (cnts[i][j] == cnts[now.first][now.second] + 1)
						{
							ways[i][j] += ways[now.first][now.second];
						}
						
						if (!vis[i][j])
						{
							vis[i][j] = true;
							qu.emplace(pii{i, j});
						}
						
						//qu.emplace(pii{i, j});
						break;
					}
				}
		}

		printf("CASE#%d: %d %d", kase++, cnts[n][m] + fix, ways[n][m]);
		
		pii p{n, m};
		deque<pii> dq;
		while(!(p.first == 1 && p.second == 1))
		{
			if (g[p.first][p.second])
				dq.emplace_front(p);
			p = from[p.first][p.second];
		}
		if (g[1][1])
			dq.emplace_front(p);
		
		if (dq.size())
		{
			printf(" %d", (dq[0].first - 1) * m + dq[0].second);
			for (auto it = dq.begin() + 1; it != dq.end(); ++it)
			{
				printf(" %d", ((*it).first - 1) * m + (*it).second);
			}
		}
		puts("");
	}
	return 0;
}
