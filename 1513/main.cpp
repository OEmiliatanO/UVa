#include <iostream>
#include <cstring>
#include <map>

#define low(x) (x&(-x))

using namespace std;

constexpr int MAXN = 2e5 + 4;

int64_t BIT[MAXN];
map<int, int> M;

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
		M.clear();
		memset(BIT, 0, sizeof(BIT));

		int n, m, base;
		scanf("%d %d", &n, &m);
		base = m;
		for (int i = 1; i <= n; ++i)
		{
			add(base + i, 1LL);
			if (require(base + i) != i)
				cout << "i = " << i << '\n';
			M[i] = base + i;
		}

		while(m--)
		{
			int x;
			int64_t res;
			scanf("%d", &x);
			//cout << "x=" << x << '\n';
			res = require(M[x]);
			//cout << "req(x) = " << require(x) << '\n';
			printf("%ld%c", res - 1, " \n"[m == 0]);
			add(base, 1LL);
			add(M[x], -1);
			M[x] = base;
			--base;
		}
	}
	return 0;
}
