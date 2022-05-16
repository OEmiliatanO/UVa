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

int cnts[MAXN * MAXN + 10];
int ways[MAXN * MAXN + 10];
int from[MAXN * MAXN + 10];
int pts[MAXN * MAXN + 10];
bool g[MAXN + 5][MAXN + 5];

int main()
{
	int n, m, kase = 1;
	while(~scanf("%d %d", &n, &m) && !(n == -1 && m == -1))
	{
		memset(cnts, 0, sizeof(cnts));
		memset(g, false, sizeof(g));
		memset(ways, 0, sizeof(ways));
		memset(from, -1, sizeof(from));
		
		int x, y, L = 0;
		
		while(scanf("%d %d", &x, &y) && !(x == 0 && y == 0))
			g[x][y] = true;

		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				if (g[i][j]) pts[L++] = (i - 1) * m + j;

		
		if (!g[n][m]) pts[L++] = n * m;

		for (int i = 0; i < L; ++i)
		{
			ways[i] = cnts[i] = 1;
			from[i] = -1;
			for (int j = 0; j < i; ++j)
				if ((pts[j] - 1) % m <= (pts[i] - 1) % m)
				{
					if (cnts[i] < cnts[j] + 1)
					{
						from[i] = j;
						cnts[i] = cnts[j] + 1;
						ways[i] = ways[j];
					}
					else if (cnts[i] == cnts[j] + 1)
						ways[i] += ways[j];
				}
		}

		if (!g[n][m]) --cnts[L - 1];
		printf("CASE#%d: %d %d", kase++, cnts[L - 1], ways[L - 1]);
		
		int p = L - 1;
		deque<int> dq;
		while(p != -1)
		{
			dq.emplace_front(pts[p]);
			p = from[p];
		}
		if (!g[n][m])
			dq.pop_back();
		
		if (dq.size())
			for (auto it = dq.begin(); it != dq.end(); ++it)
				printf(" %d", *it);

		puts("");
	}
	return 0;
}
