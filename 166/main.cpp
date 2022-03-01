#include <iostream>
#include <cstring>
#define UNDEFINED 0x3f3f3f3f

using namespace std;

constexpr int MAXN = 500;
constexpr int coin[] = {5, 10, 20, 50, 100, 200};

int cnt[MAXN + 10];
int dp[MAXN + 10];

void init()
{
	memset(cnt, UNDEFINED, sizeof(int) * (MAXN + 10));
	cnt[0] = 0;
	for (auto v : coin)
	{
		for (int t = v; t <= MAXN; ++t)
			cnt[t] = min(cnt[t], cnt[t - v] + 1);
	}

	/*
	printf("debug:\n");
	for (int i = 0; i <= 50; ++i)
	{
		if (cnt[i] == UNDEFINED) printf("x ");
		else printf("%d ", cnt[i]);
	}
	putchar('\n');
	*/
}

int main()
{
	init();

	int coincnt[6];
	while(~scanf("%d %d %d %d %d %d", coincnt, coincnt + 1, coincnt + 2, coincnt + 3, coincnt + 4, coincnt + 5) && (coincnt[0] || coincnt[1] || coincnt[2] || coincnt[3] || coincnt[4] || coincnt[5]))
	{
		memset(dp, UNDEFINED, sizeof(int) * (MAXN + 10));
		dp[0] = 0;

		int D, F, tg;
		scanf("%d.%d", &D, &F);

		tg = D * 100 + F;
		for (int i = 0; i < 6; ++i)
		{
			int v = coin[i];
			for (int j = 0; j < coincnt[i]; ++j)
			{
				for (int t = MAXN; t >= v; --t)
				{
					dp[t] = min(dp[t], dp[t - v] + 1);
				}
			}
		}

		int ans = UNDEFINED;
		for (int i = tg; i <= MAXN; ++i)
		{
			ans = min(ans, dp[i] + cnt[i - tg]);
		}

		printf("%3d\n", ans);
	}
}
