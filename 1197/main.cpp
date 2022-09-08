#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

constexpr int maxn = 30000;

int arr[maxn + 1];

int find(int x)
{
	return (arr[x] = (arr[x] == x ? x : find(arr[x])));
}

int main()
{
	int n, m;
	while (cin >> n >> m, n || m)
	{
		int ans = 0;
		for (int i = 0; i < n; ++i) arr[i] = i;

		while (m--)
		{
			int tot, x, head;
			cin >> tot >> head;
			--tot;
			while (tot--)
			{
				cin >> x;
				arr[find(x)] = find(head);
			}
		}
		for (int i = 0; i < n; ++i)
			ans += (find(i) == find(0));
		cout << ans << '\n';
	}
	return 0;
}
