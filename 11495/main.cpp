#include <iostream>
#include <algorithm>
#include <cstring>

#define lowbit(x) ((x) & (~(x)+1))

using namespace std;

constexpr int maxn = (int)1e5;
int64_t arr[maxn + 1];

int64_t BIT[maxn + 1];
void add(int pos, int64_t val)
{
	for (int i = pos; i <= maxn; i += lowbit(i))
		BIT[i] += val;
}

int64_t require(int pos)
{
	int64_t res = 0;
	for (int i = pos; i; i -= lowbit(i))
		res += BIT[i];
	return res;
}

int main()
{
	int n;
	while (cin >> n, n)
	{
		memset(BIT, 0, sizeof(int64_t) * n);

		int64_t sum = 0;
		for (int i = 0; i < n; ++i)
			cin >> arr[i];

		for (int i = n - 1; i >= 0; --i)
		{
			add(arr[i], 1);
			sum += require(arr[i] - 1);
		}

		if (sum & 1)
			cout << "Marcelo"  << '\n';
		else
			cout << "Carlos" << '\n';
	}
	return 0;
}
