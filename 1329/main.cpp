#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>

using namespace std;

constexpr int maxn = 20000;
constexpr int m = 1000;

int arr[maxn + 1];

int find(int x, long long& ans)
{
#ifdef DEBUGing
	printf("find(%d, %d)\n", x, ans);
#endif
	return (arr[x] == x ? x : find(arr[x], ans += abs(x - arr[x]) % m));
}

int main()
{
	int T;
	scanf("%d%*c", &T);
	while (T--)
	{
		int n;
		long long ans;
		char op;
		scanf("%d%*c", &n);

		for (int i = 0; i <= n; ++i) arr[i] = i;

		while(~scanf("%c", &op) && op != 'O')
		{
#ifdef DEBUGing
			printf("op: %c\n", op);
#endif
			if (op == 'E')
			{
				ans = 0;
				int x;
				scanf("%d%*c", &x);
				find(x, ans);
				printf("%lld\n", ans);
			}
			else if (op == 'I')
			{
				int x, y;
				scanf("%d %d%*c", &x, &y);
				arr[find(x, ans)] = y;
			}
			else assert(false);
		}
	}
	return 0;
}
