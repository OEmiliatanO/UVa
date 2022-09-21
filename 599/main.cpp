#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

constexpr int maxn = 30;
vector<int> G[maxn];
bool isIsol[maxn];
bool vis[maxn];

bool bfs(int root)
{
	queue<pair<int, int>> qu;
	qu.emplace(root, -1);
	while(!qu.empty())
	{
		int now = qu.front().first, pa = qu.front().second; qu.pop();
		vis[now] = true;
#ifdef DEBUGing
		printf("go in %c\n", now + 'A');
#endif
		for (auto nex : G[now])
		{
			if (nex == pa) continue;
			if (vis[nex]) return false;
#ifdef DEBUGing
			printf("\t nex is %c\n", nex + 'A');
#endif
			qu.emplace(nex, now);
		}
	}
	return true;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		char s[100];
		int ac = 0, tree = 0;

		memset(isIsol, true, sizeof(isIsol));
		memset(vis, false, sizeof(vis));
		for (int i = 0; i < maxn; ++i) G[i].clear();
		while (~scanf("%s", s) && s[0] != '*')
		{
			int u = s[1] - 'A', v = s[3] - 'A';
			G[u].emplace_back(v);
			G[v].emplace_back(u);
			isIsol[u] = (u == v);
			isIsol[v] = (v == u);
		}
		scanf("%s", s);
		for (size_t i = 0; i < strlen(s); ++i)
		{
			if (s[i] <= 'Z' && s[i] >= 'A')
			{
				if (isIsol[s[i] - 'A']) ++ac;
				else tree += bfs(s[i] - 'A');
			}
		}
		printf("There are %d tree(s) and %d acorn(s).\n", tree, ac);
	}
	return 0;
}
