#include <iostream>
#include <cstring>
#include <algorithm>

#define UNDEFINED 0x7f7f7f7f

using namespace std;

constexpr int MAXN = 15;

int h, k;
int coin[2][MAXN];
int _maxcov = -1;
int dp[MAXN][10000];

void dfs(int h, int kind = 1, int st = 1, int ed = 1)
{
	for (int v = st; v <= ed; ++v)
	{
		int maxcov = v * h;
		coin[1][kind] = v;
		memcpy(&dp[kind], &dp[kind - 1], sizeof(int) * 10000);
		for (int j = v; j <= v * h; ++j)
		{
			dp[kind][j] = min(dp[kind][j], dp[kind][j - v] + 1);
			if (dp[kind][j] >= h + 1 && maxcov == v * h)
			{
				maxcov = j - 1;
				//break; // maybe next will be less, and that might effect the next level result.
			}
		}
		
		/*
		printf("kind = %d, v = %d, maxcov = %d\n", kind, v, maxcov);
		for (int i = 0; i <= v * h; ++i)
		{
			if (dp[kind][i] == UNDEFINED) printf("x ");
			else printf("%d ", dp[kind][i]);
		}
		putchar('\n');
		*/

		if (kind >= k)
		{
			if (_maxcov < maxcov)
			{
				/*
				printf("now using coin: ");
				for (int i = 1; i <= kind; ++i) printf("%d ", coin[1][i]);
				putchar('\n');
				printf("maxcov = %d\n", maxcov);
				for (int j = 1; j <= kind; ++j)
				{
					for (int i = 0; i <= v * h; ++i)
					{
						if (dp[j][i] == UNDEFINED) printf("x ");
						else printf("%d ", dp[j][i]);
					}
					putchar('\n');
				}
				*/

				memcpy(&coin[0], &coin[1], sizeof(int) * MAXN);
				_maxcov = maxcov;
			}
			continue;
		}

		dfs(h, kind + 1, v + 1, maxcov + 1);
	}
	return;
}

int main()
{
	memset(dp, UNDEFINED, sizeof(int) * 10000 * MAXN);
	dp[0][0] = 0;
	while(~scanf("%d %d", &h, &k) && (h || k))
	{
		_maxcov = -1;
		dfs(h);
		//if (h == 0 || k == 0) _maxcov = 0;
		for (int i = 1; i <= k; ++i)
		{
			printf("%3d", coin[0][i]);
		}
		printf(" ->%3d\n", _maxcov);
	}

	return 0;
}
