#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

constexpr int MAXN = 30;

struct cube
{
	int l, w, h;
	cube(int a, int b, int c) : l(a), w(b), h(c) {}
};

int n, in[MAXN * 3 + 5], dp[MAXN * 3 + 5];
vector<cube> arr;
vector<int> G[MAXN * 3 + 5];
queue<int> qu;

int main()
{
	int kase = 0;
	while(~scanf("%d", &n) && n)
	{
		memset(in, 0, sizeof(in));
		memset(dp, 0, sizeof(dp));
		arr.clear();
		for (auto& it : G)
			it.clear();

		for (int i = 0; i < n; ++i)
		{
			int a,b,c;
			scanf("%d %d %d", &a, &b, &c);
			arr.emplace_back(a,b,c); arr.emplace_back(b,c,a); arr.emplace_back(a,c,b);
		}
		for (vector<cube>::size_type i = 0; i < arr.size(); ++i)
		{
			for (vector<cube>::size_type j = 0; j < arr.size(); ++j)
			{
				if (i == j) continue;
				if ((arr[i].l < arr[j].l && arr[i].w < arr[j].w) || (arr[i].l < arr[j].w && arr[i].w < arr[j].l))
				{
					G[i].emplace_back(j);
					//printf("%d to %d\n", i, j);
					++in[j];
				}
			}
		}

		int ans = 0;
		for (int i = 0; (vector<cube>::size_type)i < arr.size(); ++i)
			if (!in[i])
			{
				qu.emplace(i);
				dp[i] = arr[i].h;
				ans = max(ans, dp[i]);
			}
		
		while(!qu.empty())
		{
			int now = qu.front(); qu.pop();
			for (auto to : G[now])
			{
				--in[to];
				if (!in[to]) qu.emplace(to);
				dp[to] = max(dp[to], dp[now] + arr[to].h);
				ans = max(ans, dp[to]);
			}
		}
		printf("Case %d: maximum height = %d\n", ++kase, ans);
	}
	
	return 0;
}
