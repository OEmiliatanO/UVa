#include <iostream>
#include <cstring>

#define low(x) (x&(-x))

using namespace std;

constexpr int MAXN = 1e5;

int64_t BIT[MAXN + 2];

void add(int pos, int64_t val)
{
	for (int i = pos; i <= MAXN; i += low(i))
		BIT[i] += val;
}

int64_t require(int pos)
{
	int64_t res = 0;
	for (int i = pos; i; i -= low(i))
		res += BIT[i];
	return res;
}

int main()
{
	int T;

	scanf("%d", &T);
	while(T--)
	{
		memset(BIT, 0, sizeof(BIT));

		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; ++i)
			add(i, 1LL);

		while(m--)
		{
			int x;
			int64_t res;
			scanf("%d", &x);
			//cout << "x=" << x << '\n';
			res = require(x);
			//cout << "req(x) = " << require(x) << '\n';
			printf("%ld%c", res - 1, " \n"[m == 0]);
			add(1, 1LL);
			add(res, -1);
			add(x, -res + 1);
			add(x + 1, res - 1);
		}
	}
	return 0;
}
