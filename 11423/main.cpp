#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#define lowbit(x) ((-(x)) & (x))

using namespace std;

constexpr int MAXN = (int)1e7;
constexpr int MAXC = 30;
constexpr int MAXSTAT = 20000;

int BIT[MAXN + 1]{};

void add(int pos, int val)
{
	if (pos <= 0) return;
	for (; pos < MAXN; pos += lowbit(pos))
		BIT[pos] += val;
}

int query(int pos)
{
	if (pos <= 0) return 0;
	int res = 0;
	for (; pos > 0; pos -= lowbit(pos))
		res += BIT[pos];
	return res;
}

int T = 1;
int ask[MAXN + 10][2]{};
int cache[MAXC + 10];
int miss[MAXC + 10]{};
char s[10];
map<int, int> table;

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", &cache[i]);
	getchar();
	while(~scanf("%s%*c", s) && s[0] != 'E')
	{
		if (s[0] == 'R')
		{
			int s, k, c;
			scanf("%d %d %d%*c", &s, &k, &c);
			for (int i = 0; i < c; ++i)
			{
				int req = s + i * k;
				ask[T][0] = req;
				if (table.find(req) != table.end())
					ask[T][1] = table[req];
				else
					ask[T][1] = -1;
				table[req] = T++;
			}
		}
		else if (s[0] == 'A')
		{
			int req;
			scanf("%d", &req);
			ask[T][0] = req;
			if (table.find(req) != table.end())
				ask[T][1] = table[req];
			else
				ask[T][1] = -1;
			table[req] = T++;
		}
		else if (s[0] == 'S')
			ask[T++][0] = -1;
	}

	for (int t = 1; t < T; ++t)
	{
		if (ask[t][0] == -1)
		{
			for (int i = 0; i < n - 1; ++i)
				printf("%d ", miss[i]);
			printf("%d\n", miss[n - 1]);
			memset(miss, 0, sizeof(miss));
		}
		else
		{
			add(t, 1);
			if (ask[t][1] == -1)
			{
				for (int i = 0; i < n; ++i)
					++miss[i];
			}
			else if (ask[t][1] > 0)
			{
				int dis = query(t) - query(ask[t][1]);
				for (int i = 0; i < n; ++i)
					miss[i] += (cache[i] < dis);
				add(ask[t][1], -1);
			}
		}
	}

	return 0;
}
