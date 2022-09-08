#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

constexpr int maxn = (int)1e5;

int arr[maxn + 1];
int ans[230];

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		memset(ans, 0, sizeof(int) * 230);
		
		int n, q, x;
		scanf("%d %d", &n, &q);
		
		for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);
		
		for (int i = 0; i < 230; ++i)
			for (int j = 0; j < n; ++j)
				ans[i] = max(ans[i], arr[j] & i);

		while(q--)
		{
			scanf("%d", &x);
			printf("%d\n", ans[x]);
		}
	}
	return 0;
}
