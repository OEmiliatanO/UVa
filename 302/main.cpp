#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
#include <cassert>

using namespace std;

constexpr int MAXV = 44;
constexpr int MAXE = 1995;

typedef pair<int, int> pii;

vector<int> vec[MAXV + 1];
pii edge[MAXE + 1];

int maxe;

bool ECircle_exist()
{
	for (int i = 1; i <= MAXV; ++i)
		if (vec[i].size() & 1)
			return false;
	return true;
}

bool walked[MAXE + 1];
deque<int> st;
void dfs(int now)
{
	for (auto it : vec[now])
	{
		if (walked[it]) continue;
		int nex = (edge[it].first == now ? edge[it].second : edge[it].first);

		walked[it] = true;

		dfs(nex);
		st.emplace_front(it);
	}
}

int main()
{
	char s[1000];
	int x, y, z;
	while(true)
	{
		st.clear();
		memset(walked, 0, sizeof(walked));
		for (int i = 0; i <= MAXV; ++i)
			vec[i].clear();
		maxe = -1;

		int cnt = 0;
		int start = -1;
		while(~scanf("%[^\n]s", s))
		{
			getchar();
			++cnt;
			if (sscanf(s, "%d %d %d", &x, &y, &z) != 3)
				break;
			
			maxe = max(maxe, z);
			if (cnt == 1) start = min(x, y);

			vec[x].emplace_back(z);
			vec[y].emplace_back(z);
			edge[z] = {x, y};
		}
		if (cnt <= 1) break;

		if (ECircle_exist())
		{
			for (int i = 1; i <= MAXV; ++i)
				if (vec[i].size()) sort(vec[i].begin(), vec[i].end());
			
			assert(start != -1);
			dfs(start);

			for (int i = 0; i < st.size(); ++i)
				printf("%d%c", st[i], " \n"[(i == st.size() - 1)]);
		}
		else
			printf("Round trip does not exist.\n");

		puts("");
	}
	return 0;
}
