#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

typedef pair<int, int> pii;

constexpr int MAXN = 100;

int cnts[MAXN + 5][MAXN + 5];
int ways[MAXN + 5][MAXN + 5];

int main()
{
	int n, m;
	while(~scanf("%d %d", &n, &m) && !(n == -1 && m == -1))
	{
		memset(cnts, 0, sizeof(cnts));
		memset(ways, 0, sizeof(ways));

		queue<pii> qu;
		int fix = -2;
		while(scanf("%d %d", &x, &y) && !(x == 0 && y == 0))
		{
			cnts[x][y] = 1;
			if (x == 1 && y == 1)
				++fix;
			else if (x == n && y == m)
				++fix;
		}
		
		if (fix > 0) fix = 0;
		qu.emplace(1, 1);
		cnts[1][1] = cnts[n][m] = 1;
		while(qu.size())
		{
			pii now = qu.front(); qu.pop();
			int upperm = m;
			for (int i = now.first; i <= n; ++i)
				for (int j = now.second; j <= upperm; ++j)
				{
					if (cnts[i][j])
					{
						upperm = min(upperm, j);
						cnts[i][j] = max(cnts[i][j], cnt[now.first][now.second] + 1);
						ways[i][j] = 
						break;
					}
				}
		}
	}
	return 0;
}
