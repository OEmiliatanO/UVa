#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <cmath>
#include <cassert>
#include <cstring>

#define UNDEFINED 0

using namespace std;

constexpr int MAXN = 100;

vector<int> G[MAXN + 1];

int low[MAXN + 1], dep[MAXN + 1], ans;
void dfs(int now = 1, int pa = 0)
{
	bool cutv = false;
	int childcnt = 0;
	low[now] = dep[now] = dep[pa] + 1;
	for (auto nex : G[now])
	{
		if (nex == pa) continue;
		if (!dep[nex])
		{
			++childcnt;
			dfs(nex, now);
			low[now] = min(low[now], low[nex]);
			cutv |= (dep[now] <= low[nex]);
		}
		else low[now] = min(low[now], dep[nex]);
	}

	if (now == 1) ans += (childcnt >= 2);
	else ans += (int)cutv;
}

int main()
{
	int N;
	while(cin >> N && N)
	{
		assert(N <= 100 && N > 0);
		ans = 0;
		for (int i = 0; i < MAXN + 1; ++i)
		{
			G[i].clear();
			dep[i] = low[i] = UNDEFINED;
		}

		int x;
		while(cin >> x && x)
		{
			int v;
			while(cin >> v)
			{
				G[x].emplace_back(v);
				G[v].emplace_back(x);
				if (getchar() == '\n') break;
			}
		}

		dfs();
		cout << ans << '\n';
	}
	return 0;
}
