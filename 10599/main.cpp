#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

typedef pair<int, int> pii;

constexpr int MAXN = 100;

int ways[MAXN + 1][MAXN + 1];
int cnts[MAXN + 1][MAXN + 1];
int from[MAXN + 1][MAXN + 1];
bool inqu[MAXN + 1][MAXN + 1];
vector<pii> xy, yx;

int main()
{
	cout << "1" << endl;
	int n, m;
	while(~scanf("%d %d", &n, &m) && !(n == -1 && m == -1))
	{
		memset(ways, 0, sizeof(ways));
		memset(cnts, 0, sizeof(cnts));
		memset(inqu, 0, sizeof(inqu));
		xy.clear(); yx.clear();

		queue<pii> qu;
		int x, y;

		while(scanf("%d %d", &x, &y) && !(x == 0 && y == 0))
		{
			++cnts[x][y];
			xy.emplace_back(x, y);
			yx.emplace_back(y, x);
		}
		if (cnts[n][m] <= 0)
		{
			xy.emplace_back(n, m);
			yx.emplace_back(m, n);
		}

		sort(xy.begin(), xy.end());
		sort(yx.begin(), yx.end());

		qu.emplace(1, 1);
		ways[1][1] = 1;
		while(qu.size())
		{
			pii t = qu.front(); qu.pop();
			auto p = lower_bound(xy.begin(), xy.end(), t);
			auto k = lower_bound(yx.begin(), yx.end(), pii{t.second, t.first});

			if (p != xy.end())
			{
				int xx = (*p).first;
				while(p->first == xx)
				{
					ways[p->first][p->second] += ways[t.first][t.second];
					if (cnts[t.first][t.second] + 1 > cnts[p->first][p->second])
					{
						cnts[p->first][p->second] = cnts[t.first][t.second] + 1;
						from[p->first][p->second] = t.first * n + t.second;
					}
					if (!inqu[p->first][p->second])
					{
						qu.emplace(*p);
						inqu[p->first][p->second] = true;
					}
					++p;
				}
			}

			if (k != yx.end())
			{
				int yy = k->first;
				while(k->first == yy)
				{
					ways[k->second][k->first] += ways[t.first][t.second];
					if (cnts[t.first][t.second] + 1 > cnts[k->second][k->first])
					{
						cnts[k->second][k->first] = cnts[t.first][t.second] + 1;
						from[k->second][k->first] = t.first * n + t.second;
					}
					if (!inqu[k->second][k->first])
					{
						qu.emplace(*k);
						inqu[k->second][k->first] = true;
					}
					++k;
				}
			}
		}

		printf("%d %d", cnts[n][m], ways[n][m]);
		puts("");
	}
	return 0;
}
