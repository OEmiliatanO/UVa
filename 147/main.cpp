#include <iostream>
#include <cstring>
#define int long long
using namespace std;

constexpr int MAXN = 30000;
constexpr int v[] = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};

int dp[MAXN + 1];

int32_t main()
{
	int D, F;
	while(~scanf("%lld.%lld", &D, &F) && (D || F))
	{
		int tg = D * 100 + F;

		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		
		for (auto vi : v)
		{
			for (int j = vi; j <= tg; ++j)
			{
				dp[j] += dp[j - vi];
			}
		}

		printf("%3lld.", D);
		if (F < 10) printf("%02lld", F);
		else printf("%lld", F);
		printf("%17lld\n", dp[tg]);
	}
	return 0;
}
